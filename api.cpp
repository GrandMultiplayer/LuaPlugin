#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <map>
#include <chrono>
#include <atomic>

#include "api.h"

// Math
#include "sdk/CVector2.h"
#include "sdk/CVector3.h"
#include "sdk/CVector4.h"
#include "sdk/Plane.h"
#include "sdk/Quaternion.h"
#include "sdk/util.h"

#include "sdk/CMaths.h"
#include "sdk/Structs.h"

// API Function Imports
#include "sdk/APICef.h"
#include "sdk/APIVisual.h"
#include "sdk/APIWorld.h"
#include "sdk/APIEntity.h"
#include "sdk/APICheckpoint.h"
#include "sdk/APINpc.h"
#include "sdk/APIObject.h"
#include "sdk/APIPlayer.h"
#include "sdk/APIServer.h"
#include "sdk/APIVehicle.h"
#include "sdk/APIBlip.h"
#include "sdk/APIPickup.h"
#include "sdk/APICamera.h"
#include "sdk/APILog.h"

extern "C" {
	#include "inc_lua/lua.h"
	#include "inc_lua/lualib.h"
	#include "inc_lua/lauxlib.h"
}

#include "LuaBridge/LuaBridge.h"
#include "LuaBridge/RefCountedPtr.h"
#include "LuaBridge/RefCountedObject.h"

// MySQl
#include "Mysql/mysql.h"
#include "Mysql.h"

// Other
#include "Timers.h"
#include "Events.h"

using namespace luabridge;

typedef RefCountedObjectType <int> RefCountedObject;

std::vector<timer> timers;
std::vector<Event> events;

// API Lua Functions
#include "LuaVector3.h"
#include "LuaServer.h"
#include "LuaPlayer.h"
#include "LuaNpc.h"
#include "LuaVehicle.h"
#include "LuaCheckpoint.h"
#include "LuaObject.h"
#include "LuaVisual.h"
#include "LuaWorld.h"
#include "LuaMysql.h"
#include "LuaTimer.h"
#include "LuaBlip.h"
#include "LuaEvents.h"
#include "LuaEntity.h"
#include "LuaPickup.h"

char scriptName[64] = "resources//lua//main.lua";
lua_State* stateLua;

MysqlConnection	*mysql = nullptr;

void TimerTick()
{
	if (timers.empty())
		return;

	for (unsigned int i = 0; i < timers.size(); i++)
	{
		if (timers[i].used)
		{
			if (std::chrono::duration_cast<std::chrono::milliseconds>(timers[i].lastTick.time_since_epoch()).count() + timers[i].tick
				<= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
			{
				timers[i].lastTick = std::chrono::system_clock::now();

				lua_rawgeti(stateLua, LUA_REGISTRYINDEX, timers[i].functionKey);

				if (lua_isfunction(stateLua, -1))
				{
					for (unsigned int a = 0; a < timers[i].args.size(); a++)
					{
						switch (timers[i].args[a].type)
						{
						case TYPE_BOOLEAN:
							lua_pushboolean(stateLua, timers[i].args[a].boolean);
							break;
						case TYPE_STRING:
							lua_pushstring(stateLua, timers[i].args[a].string.c_str());
							break;
						case TYPE_NUMBER:
							lua_pushnumber(stateLua, timers[i].args[a].number);
							break;
						case TYPE_OTHER:
							lua_rawgeti(stateLua, LUA_REGISTRYINDEX, timers[i].args[a].other);
							break;
						}
					}

					const int error = lua_pcall(stateLua, timers[i].args.size(), 1, 0);
					if (error != 0)
					{
						std::stringstream str;
						str << "Error: %s" << lua_tostring(stateLua, -1);
						API::Log::Error(str.str());
					}
				}

				lua_pop(stateLua, 1);
			}
		}
	}
}

#pragma region CallBacks
extern "C" DLL_PUBLIC bool API_Initialize(void) 
{
	stateLua = luaL_newstate();
	API::Log::Print("Lua: Lua state created.");

	luaL_openlibs(stateLua);
	API::Log::Print("Lua: Previous libraries opened.");

	setHideMetatables(false);
	
	getGlobalNamespace(stateLua)
		.beginClass <Vector3>("Vector3")
			.addConstructor <void(*)(float, float, float)>()
			.addProperty("x", &VecHelper::get <0>, &VecHelper::set <0>)
			.addProperty("y", &VecHelper::get <1>, &VecHelper::set <1>)
			.addProperty("z", &VecHelper::get <2>, &VecHelper::set <2>)
		.endClass()
		.beginClass <Vehicle>("Vehicle")
			.addConstructor <void(*)(void)>()
			.addData("id", &Vehicle::entity, false)
			.addData("type", &Vehicle::type, false)
			.addCFunction("Create", &Vehicle::Create)
			.addCFunction("Destroy", &Vehicle::Destroy)
			.addCFunction("SetPosition", &Vehicle::SetPosition)
			.addCFunction("GetPosition", &Vehicle::GetPosition)
			.addCFunction("GetRotation", &Vehicle::GetRotation)
			.addCFunction("SetRotation", &Vehicle::SetRotation)
			.addCFunction("GetViewDistance", &Vehicle::GetViewDistance)
			.addCFunction("SetViewDistance", &Vehicle::SetViewDistance)
			.addCFunction("GetStandardColor", &Vehicle::GetStandardColor)
			.addCFunction("GetStandardColorType", &Vehicle::GetStandardColorType)
			.addCFunction("SetStandardColor", &Vehicle::SetStandardColor)
			.addCFunction("GetCustomColor", &Vehicle::GetCustomColor)
			.addCFunction("SetCustomColor", &Vehicle::SetCustomColor)
			.addCFunction("GetNumberPlate", &Vehicle::GetNumberPlate)
			.addCFunction("SetNumberPlate", &Vehicle::SetNumberPlate)
			.addCFunction("GetMod", &Vehicle::GetMod)
			.addCFunction("SetMod", &Vehicle::SetMod)
			.addCFunction("GetEngineState", &Vehicle::GetEngineState)
			.addCFunction("SetEngineState", &Vehicle::SetEngineState)
			.addCFunction("GetDoorsLockState", &Vehicle::GetDoorsLockState)
			.addCFunction("SetDoorsLockState", &Vehicle::SetDoorsLockState)
			.addCFunction("SetDoorsLockStateForPlayer", &Vehicle::SetDoorsLockStateForPlayer)
			.addCFunction("GetModel", &Vehicle::GetModel)
			.addCFunction("GetNumberPlateStyle", &Vehicle::GetNumberPlateStyle)
			.addCFunction("SetNumberPlateStyle", &Vehicle::SetNumberPlateStyle)
			.addCFunction("GetExtra", &Vehicle::GetExtra)
			.addCFunction("SetExtra", &Vehicle::SetExtra)
			.addCFunction("GetEngineHealth", &Vehicle::GetEngineHealth)
			.addCFunction("SetEngineHealth", &Vehicle::SetEngineHealth)
			.addCFunction("GetFuelTankHealth", &Vehicle::GetFuelTankHealth)
			.addCFunction("SetFuelTankHealth", &Vehicle::SetFuelTankHealth)
			.addCFunction("FixDeformation", &Vehicle::FixDeformation)
			.addCFunction("GetOccupant", &Vehicle::GetOccupant)
			.addCFunction("GetOccupants", &Vehicle::GetOccupants)
			.addCFunction("GetTaxiLightState", &Vehicle::GetTaxiLightState)
			.addCFunction("SetTaxiLightState", &Vehicle::SetTaxiLightState)
			.addCFunction("GetIndicatorState", &Vehicle::GetIndicatorState)
			.addCFunction("SetIndicatorState", &Vehicle::SetIndicatorState)
			.addCFunction("GetInteriorLightState", &Vehicle::GetInteriorLightState)
			.addCFunction("SetInteriorLightState", &Vehicle::SetInteriorLightState)
			.addCFunction("GetSirenSoundState", &Vehicle::GetSirenSoundState)
			.addCFunction("SetSirenSoundState", &Vehicle::SetSirenSoundState)
			.addCFunction("CreateBlip", &Vehicle::CreateBlip)
			.addCFunction("ShowBlip", &Vehicle::ShowBlip)
			.addCFunction("HideBlip", &Vehicle::HideBlip)
			.addCFunction("GetBlipColor", &Vehicle::GetBlipColor)
			.addCFunction("SetBlipColor", &Vehicle::SetBlipColor)
			.addCFunction("GetBlipSprite", &Vehicle::GetBlipSprite)
			.addCFunction("SetBlipSprite", &Vehicle::SetBlipSprite)
			.addCFunction("GetBlipText", &Vehicle::GetBlipText)
			.addCFunction("SetBlipText", &Vehicle::SetBlipText)
			.addCFunction("IsBlipShortRanged", &Vehicle::IsBlipShortRanged)
			.addCFunction("SetBlipShortRanged", &Vehicle::SetBlipShortRanged)
			.addCFunction("ShowBlipToAll", &Vehicle::ShowBlipToAll)
			.addCFunction("HideBlipFromAll", &Vehicle::HideBlipFromAll)
			.addCFunction("GetHealth", &Vehicle::GetHealth)
			.addCFunction("SetHealth", &Vehicle::SetHealth)
			.addCFunction("IsAlive", &Vehicle::IsAlive)
			.addCFunction("GetTowedVehicle", &Vehicle::GetTowedVehicle)
			.addCFunction("SetTowedVehicle", &Vehicle::SetTowedVehicle)
			.addCFunction("IsTowed", &Vehicle::IsTowed)
		.endClass()
		.beginClass <Checkpoint>("Checkpoint")
			.addConstructor <void(*)(void)>()
			.addData("id", &Checkpoint::entity, false)
			.addData("type", &Checkpoint::type, false)
			.addCFunction("Create", &Checkpoint::Create)
			.addCFunction("Destroy", &Checkpoint::Destroy)
			.addCFunction("GetPosition", &Checkpoint::GetPosition)
			.addCFunction("SetPosition", &Checkpoint::SetPosition)
			.addCFunction("Show", &Checkpoint::Show)
			.addCFunction("Hide", &Checkpoint::Hide)
			.addCFunction("GetNearHeight", &Checkpoint::GetNearHeight)
			.addCFunction("SetNearHeight", &Checkpoint::SetNearHeight)
			.addCFunction("GetFarHeight", &Checkpoint::GetFarHeight)
			.addCFunction("SetFarHeight", &Checkpoint::SetFarHeight)
			.addCFunction("GetViewDistance", &Checkpoint::GetViewDistance)
			.addCFunction("SetViewDistance", &Checkpoint::SetViewDistance)
			.addCFunction("GetPointTo", &Checkpoint::GetPointTo)
			.addCFunction("PointTo", &Checkpoint::PointTo)
			.addCFunction("GetType", &Checkpoint::GetType)
			.addCFunction("SetType", &Checkpoint::SetType)
			.addCFunction("CreateBlip", &Checkpoint::CreateBlip)
			.addCFunction("ShowBlip", &Checkpoint::ShowBlip)
			.addCFunction("HideBlip", &Checkpoint::HideBlip)
			.addCFunction("GetBlipColor", &Checkpoint::GetBlipColor)
			.addCFunction("SetBlipColor", &Checkpoint::SetBlipColor)
			.addCFunction("GetBlipSprite", &Checkpoint::GetBlipSprite)
			.addCFunction("SetBlipSprite", &Checkpoint::SetBlipSprite)
			.addCFunction("GetBlipText", &Checkpoint::GetBlipText)
			.addCFunction("SetBlipText", &Checkpoint::SetBlipText)
			.addCFunction("IsBlipShortRanged", &Checkpoint::IsBlipShortRanged)
			.addCFunction("SetBlipShortRanged", &Checkpoint::SetBlipShortRanged)
			.addCFunction("ShowBlipToAll", &Checkpoint::ShowBlipToAll)
			.addCFunction("HideBlipFromAll", &Checkpoint::HideBlipFromAll)
		.endClass()
		.beginClass <Object>("Object")
			.addConstructor <void(*)(void)>()
			.addData("id", &Object::entity, false)
			.addData("type", &Object::type, false)
			.addCFunction("Create", &Object::Create)
			.addCFunction("Destroy", &Object::Destroy)
			.addCFunction("SetPosition", &Object::SetPosition)
			.addCFunction("GetPosition", &Object::GetPosition)
			.addCFunction("GetRotation", &Object::GetRotation)
			.addCFunction("SetRotation", &Object::SetRotation)
			.addCFunction("GetViewDistance", &Object::GetViewDistance)
			.addCFunction("SetViewDistance", &Object::SetViewDistance)
			.addCFunction("GetTextureVariation", &Object::GetTextureVariation)
			.addCFunction("SetTextureVariation", &Object::SetTextureVariation)
			.addCFunction("CreateBlip", &Object::CreateBlip)
			.addCFunction("ShowBlip", &Object::ShowBlip)
			.addCFunction("HideBlip", &Object::HideBlip)
			.addCFunction("GetBlipColor", &Object::GetBlipColor)
			.addCFunction("SetBlipColor", &Object::SetBlipColor)
			.addCFunction("GetBlipSprite", &Object::GetBlipSprite)
			.addCFunction("SetBlipSprite", &Object::SetBlipSprite)
			.addCFunction("GetBlipText", &Object::GetBlipText)
			.addCFunction("SetBlipText", &Object::SetBlipText)
			.addCFunction("IsBlipShortRanged", &Object::IsBlipShortRanged)
			.addCFunction("SetBlipShortRanged", &Object::SetBlipShortRanged)
			.addCFunction("ShowBlipToAll", &Object::ShowBlipToAll)
			.addCFunction("HideBlipFromAll", &Object::HideBlipFromAll)
			.addCFunction("GetHealth", &Object::GetHealth)
			.addCFunction("SetHealth", &Object::SetHealth)
			.addCFunction("IsAlive", &Object::IsAlive)
		.endClass()
		.beginClass <NPC>("NPC")
			.addConstructor <void(*)(void)>()
			.addData("id", &NPC::entity, false)
			.addData("type", &NPC::type, false)
			.addCFunction("Create", &NPC::Create)
			.addCFunction("Destroy", &NPC::Destroy)
			.addCFunction("SetPosition", &NPC::SetPosition)
			.addCFunction("GetPosition", &NPC::GetPosition)
			.addCFunction("GetRotation", &NPC::GetRotation)
			.addCFunction("SetRotation", &NPC::SetRotation)
			.addCFunction("GetViewDistance", &NPC::GetViewDistance)
			.addCFunction("SetViewDistance", &NPC::SetViewDistance)
			.addCFunction("GetPedComponent", &NPC::GetPedComponent)
			.addCFunction("SetPedComponent", &NPC::SetPedComponent)
			.addCFunction("GetPedHeadBlend", &NPC::GetPedHeadBlend)
			.addCFunction("SetPedHeadBlend", &NPC::SetPedHeadBlend)
			.addCFunction("GetPedHeadOverlay", &NPC::GetPedHeadOverlay)
			.addCFunction("SetPedHeadOverlay", &NPC::SetPedHeadOverlay)
			.addCFunction("GetPedProp", &NPC::GetPedProp)
			.addCFunction("SetPedProp", &NPC::SetPedProp)
			.addCFunction("GetPedFaceFeature", &NPC::GetPedFaceFeature)
			.addCFunction("SetPedFaceFeature", &NPC::SetPedFaceFeature)
			.addCFunction("GetNametag", &NPC::GetNametag)
			.addCFunction("SetNametag", &NPC::SetNametag)
			.addCFunction("IsNametagVisible", &NPC::IsNametagVisible)
			.addCFunction("SetNametagVisible", &NPC::SetNametagVisible)
			.addCFunction("IsHealthbarVisible", &NPC::IsHealthbarVisible)
			.addCFunction("SetHealthbarVisible", &NPC::SetHealthbarVisible)
			.addCFunction("GetNametagDistance", &NPC::GetNametagDistance)
			.addCFunction("SetNametagDistance", &NPC::SetNametagDistance)
			.addCFunction("GetNametagColor", &NPC::GetNametagColor)
			.addCFunction("SetNametagColor", &NPC::SetNametagColor)
			.addCFunction("CreateBlip", &NPC::CreateBlip)
			.addCFunction("ShowBlip", &NPC::ShowBlip)
			.addCFunction("HideBlip", &NPC::HideBlip)
			.addCFunction("GetBlipColor", &NPC::GetBlipColor)
			.addCFunction("SetBlipColor", &NPC::SetBlipColor)
			.addCFunction("GetBlipSprite", &NPC::GetBlipSprite)
			.addCFunction("SetBlipSprite", &NPC::SetBlipSprite)
			.addCFunction("GetBlipText", &NPC::GetBlipText)
			.addCFunction("SetBlipText", &NPC::SetBlipText)
			.addCFunction("IsBlipShortRanged", &NPC::IsBlipShortRanged)
			.addCFunction("SetBlipShortRanged", &NPC::SetBlipShortRanged)
			.addCFunction("ShowBlipToAll", &NPC::ShowBlipToAll)
			.addCFunction("HideBlipFromAll", &NPC::HideBlipFromAll)
			.addCFunction("GetHealth", &NPC::GetHealth)
			.addCFunction("SetHealth", &NPC::SetHealth)
			.addCFunction("GetArmour", &NPC::GetArmour)
			.addCFunction("SetArmour", &NPC::SetArmour)
			.addCFunction("Reive", &NPC::Revive)
			.addCFunction("IsAlive", &NPC::IsAlive)
		.endClass()
		.beginClass <Player>("Player")
		.addConstructor <void(*)(void)>()
			.addData("id", &Player::entity, false)
			.addData("type", &Player::type, false)
			.addCFunction("SetPosition", &Player::SetPosition)
			.addCFunction("GetPosition", &Player::GetPosition)
			.addCFunction("GetRotation", &Player::GetRotation)
			.addCFunction("SetRotation", &Player::SetRotation)
			.addCFunction("GetViewDistance", &Player::GetViewDistance)
			.addCFunction("SetViewDistance", &Player::SetViewDistance)
			.addCFunction("GetPedComponent", &Player::GetPedComponent)
			.addCFunction("SetPedComponent", &Player::SetPedComponent)
			.addCFunction("GetPedHeadBlend", &Player::GetPedHeadBlend)
			.addCFunction("SetPedHeadBlend", &Player::SetPedHeadBlend)
			.addCFunction("GetPedHeadOverlay", &Player::GetPedHeadOverlay)
			.addCFunction("SetPedHeadOverlay", &Player::SetPedHeadOverlay)
			.addCFunction("GetPedProp", &Player::GetPedProp)
			.addCFunction("SetPedProp", &Player::SetPedProp)
			.addCFunction("GetPedFaceFeature", &Player::GetPedFaceFeature)
			.addCFunction("SetPedFaceFeature", &Player::SetPedFaceFeature)
			.addCFunction("GetModel", &Player::GetModel)
			.addCFunction("SetModel", &Player::SetModel)
			.addCFunction("ShowNotification", &Player::ShowNotification)
			.addCFunction("LoadIPL", &Player::LoadIPL)
			.addCFunction("UnloadIPL", &Player::UnloadIPL)
			.addCFunction("SendChatMessage", &Player::SendChatMessage)
			.addCFunction("GetUsername", &Player::GetUsername)
			.addCFunction("SetUsername", &Player::SetUsername)
			.addCFunction("ShowCursor", &Player::ShowCursor)
			.addCFunction("LoadURL", &Player::LoadURL)
			.addCFunction("JavaScriptCall", &Player::JavaScriptCall)
			.addCFunction("IsControllable", &Player::IsControllable)
			.addCFunction("SetControllable", &Player::SetControllable)
			.addCFunction("GetIP", &Player::GetIP)
			.addCFunction("GetSecretKey", &Player::GetSecretKey)
			.addCFunction("Kick", &Player::Kick)
			.addCFunction("ShowSubtitle", &Player::ShowSubtitle)
			.addCFunction("PutInVehicle", &Player::PutInVehicle)
			.addCFunction("GetVehicle", &Player::GetVehicle)
			.addCFunction("GetSeat", &Player::GetSeat)
			.addCFunction("GiveWeapon", &Player::GiveWeapon)
			.addCFunction("RemoveWeapon", &Player::RemoveWeapon)
			.addCFunction("GetNametag", &Player::GetNametag)
			.addCFunction("SetNametag", &Player::SetNametag)
			.addCFunction("IsNametagVisible", &Player::IsNametagVisible)
			.addCFunction("SetNametagVisible", &Player::SetNametagVisible)
			.addCFunction("IsHealthbarVisible", &Player::IsHealthbarVisible)
			.addCFunction("SetHealthbarVisible", &Player::SetHealthbarVisible)
			.addCFunction("GetNametagDistance", &Player::GetNametagDistance)
			.addCFunction("SetNametagDistance", &Player::SetNametagDistance)
			.addCFunction("GetNametagColor", &Player::GetNametagColor)
			.addCFunction("SetNametagColor", &Player::SetNametagColor)
			.addCFunction("CreateBlip", &Player::CreateBlip)
			.addCFunction("ShowBlip", &Player::ShowBlip)
			.addCFunction("HideBlip", &Player::HideBlip)
			.addCFunction("GetBlipColor", &Player::GetBlipColor)
			.addCFunction("SetBlipColor", &Player::SetBlipColor)
			.addCFunction("GetBlipSprite", &Player::GetBlipSprite)
			.addCFunction("SetBlipSprite", &Player::SetBlipSprite)
			.addCFunction("GetBlipText", &Player::GetBlipText)
			.addCFunction("SetBlipText", &Player::SetBlipText)
			.addCFunction("IsBlipShortRanged", &Player::IsBlipShortRanged)
			.addCFunction("SetBlipShortRanged", &Player::SetBlipShortRanged)
			.addCFunction("ShowBlipToAll", &Player::ShowBlipToAll)
			.addCFunction("HideBlipFromAll", &Player::HideBlipFromAll)
			.addCFunction("SetGroundSnow", &Player::SetGroundSnow)
			.addCFunction("SetBlackout", &Player::SetBlackout)
			.addCFunction("GetWeaponAmmo", &Player::GetWeaponAmmo)
			.addCFunction("SetWeaponAmmo", &Player::SetWeaponAmmo)
			.addCFunction("GetWeapons", &Player::GetWeapons)
			.addCFunction("EquiptWeapon", &Player::EquipWeapon)
			.addCFunction("GetHealth", &Player::GetHealth)
			.addCFunction("SetHealth", &Player::SetHealth)
			.addCFunction("GetArmour", &Player::GetArmour)
			.addCFunction("SetArmour", &Player::SetArmour)
			.addCFunction("IsHudHidden", &Player::IsHudHidden)
			.addCFunction("DisplayHud", &Player::DisplayHud)
			.addCFunction("IsRadarHidden", &Player::IsRadarHidden)
			.addCFunction("DisplayRadar", &Player::DisplayRadar)
			.addCFunction("IsCashHidden", &Player::IsCashHidden)
			.addCFunction("DisplayCash", &Player::DisplayCash)
			.addCFunction("IsAmmoHidden", &Player::IsAmmoHidden)
			.addCFunction("DisplayAmmo", &Player::DisplayAmmo)
			.addCFunction("Revive", &Player::Revive)
			.addCFunction("IsAlive", &Player::IsAlive)
				.addCFunction("SetCameraPosition", &Player::SetCameraPosition)
				.addCFunction("SetCameraRotation", &Player::SetCameraRotation)
				.addCFunction("ResetCamera", &Player::ResetCamera)
				.addCFunction("FirstPersonOnly", &Player::FirstPersonOnly)
				.addCFunction("ThirdPersonOnly", &Player::ThirdPersonOnly)
				.addCFunction("AttachCamera", &Player::AttachCamera)
				.addCFunction("DetachCamera", &Player::DetachCamera)
		.endClass()
		.beginClass <Blip>("Blip")
		.addConstructor <void(*)(void)>()
			.addData("id", &Blip::entity, false)
			.addData("type", &Blip::type, false)
			.addCFunction("Create", &Blip::Create)
			.addCFunction("SetPosition", &Blip::SetPosition)
			.addCFunction("GetPosition", &Blip::GetPosition)
			//.addCFunction("Destroy", &Blip::Destroy)
			.addCFunction("Show", &Blip::Show)
			.addCFunction("Hide", &Blip::Hide)
			.addCFunction("GetColor", &Blip::GetColor)
			.addCFunction("SetColor", &Blip::SetColor)
			.addCFunction("GetSprite", &Blip::GetSprite)
			.addCFunction("SetSprite", &Blip::SetSprite)
			.addCFunction("GetText", &Blip::GetText)
			.addCFunction("SetText", &Blip::SetText)
			.addCFunction("IsShortRanged", &Blip::IsShortRanged)
			.addCFunction("SetShortRanged", &Blip::SetShortRanged)
			.addCFunction("ShowToAll", &Blip::ShowToAll)
			.addCFunction("HideFromAll", &Blip::HideFromAll)
		.endClass()
		.beginClass <Pickup>("Pickup")
			.addConstructor <void(*)(void)>()
			.addData("id", &Pickup::entity, false)
			.addData("type", &Pickup::type, false)
			.addCFunction("Create", &Pickup::Create)
			.addCFunction("Destroy", &Pickup::Destroy)
			.addCFunction("Show", &Pickup::Show)
			.addCFunction("ShowToAll", &Pickup::ShowToAll)
			.addCFunction("HideFromAll", &Pickup::HideFromAll)
			.addCFunction("Hide", &Pickup::Hide)
			.addCFunction("GetPosition", &Pickup::GetPosition)
			.addCFunction("SetPosition", &Pickup::SetPosition)
			.addCFunction("GetModel", &Pickup::GetModel)
			.addCFunction("SetModel", &Pickup::SetModel)
			.addCFunction("GetRespawnDelay", &Pickup::GetRespawnDelay)
			.addCFunction("SetRespawnDelay", &Pickup::SetRespawnDelay)
		.endClass()
		.beginClass <Timer>("Timer")
		.addConstructor <void(*)(void)>()
			.addCFunction("Create", &Timer::Create)
			.addCFunction("Destroy", &Timer::Destroy)
		.endClass()
		.beginNamespace("visual")
			.addCFunction("ShowMessageAboveMap", Visual::ShowMessageAboveMap)
			.addCFunction("SendChatMessage", Visual::SendChatMessage)
			.addCFunction("ShowSubtitle", Visual::ShowSubtitle)
		.endNamespace()
		.beginNamespace("server")
			//.addCFunction("PrintMessage", Server::PrintMessage)
		.endNamespace()
		.beginNamespace("world")
			.addCFunction("GetTime", World::GetTime)
			.addCFunction("SetTime", World::SetTime)
			.addCFunction("GetWeather", World::GetWeather)
			.addCFunction("SetWeather", World::SetWeather)
			.addCFunction("LoadIPL", World::LoadIPL)
			.addCFunction("UnloadIPL", World::UnloadIPL)
			.addCFunction("IsBlackout", World::IsBlackout)
			.addCFunction("SetBlackout", World::SetBlackout)
			.addCFunction("IsGroundSnow", World::IsGroundSnow)
			.addCFunction("SetGroundSnow", World::SetGroundSnow)
		.endNamespace()
		.beginNamespace("entity")
			.addCFunction("GetEntities", Entity::GetEntities)
		.endNamespace()
		.beginNamespace("mysql")
			.addCFunction("Connect", Mysql::Connect)
			.addCFunction("Disconnect", Mysql::Disconnect)
			.addCFunction("Query", Mysql::Query)
		.endNamespace()
		.beginNamespace("Event")
			.addCFunction("AddHandler", Events::AddHandler)
		.endNamespace();

	// Load scripts
	if (luaL_dofile(stateLua, scriptName) != 0) {
		std::stringstream str;
		str << "Lua: Error occured when loading " << scriptName;
		API::Log::Error(str.str());

		str.clear();
		str << "Error: %s" << lua_tostring(stateLua, -1);
		API::Log::Error(str.str());
	}
	else {
		std::stringstream str;
		str << "Lua: Succesfully loaded " << scriptName;

		API::Log::Print(str.str());
	}
	
	int result = 1;


	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("oninit") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				int error = lua_pcall(stateLua, 0, 1, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}

				if (result == 1)
					result = (int)luaL_optinteger(stateLua, -1, 1);
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events


	lua_getglobal(stateLua, "OnInit");
	if (lua_isfunction(stateLua, -1))
	{
		int error = lua_pcall(stateLua, 0, 1, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnInit");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}

		result = lua_tointeger(stateLua, -1);
	}
	lua_pop(stateLua, -1);

	return result;
}

extern "C" DLL_PUBLIC bool API_Close(void)
{

	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onclose") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, timers[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				int error = lua_pcall(stateLua, 0, 0, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
				lua_pop(stateLua, 1);
			}
		}
	}


	int result;
	lua_getglobal(stateLua, "OnClose");
	if (lua_isfunction(stateLua, -1))
	{
		int error = lua_pcall(stateLua, 0, 1, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnClose");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}

		result = lua_tointeger(stateLua, -1);
	}
	lua_pop(stateLua, -1);

	lua_close(stateLua);
	return true;
}

extern "C" DLL_PUBLIC bool API_OnTick(void) 
{
	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("ontick") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				int error = lua_pcall(stateLua, 0, 1, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	int result = 1;

	lua_getglobal(stateLua, "OnTick");
	if (lua_isfunction(stateLua, -1))
	{
		int error = lua_pcall(stateLua, 0, 0, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnTick");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}
		
		//result = (int)luaL_optinteger(stateLua, -1, 1);
	}
	lua_pop(stateLua, -1);

	TimerTick();
	
	return true;
}

extern "C" DLL_PUBLIC bool API_OnPlayerConnecting(const std::string playerUid, const std::string playername)
{
	int result = 1;

	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onplayerconnecting") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				lua_pushstring(stateLua, playerUid.c_str());
				lua_pushstring(stateLua, playername.c_str());

				int error = lua_pcall(stateLua, 2, 1, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}

				if(result == 1)
					result = (int)luaL_optinteger(stateLua, -1, 1);
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnPlayerConnecting");
	if (lua_isfunction(stateLua, -1))
	{
		lua_pushstring(stateLua, playerUid.c_str());
		lua_pushstring(stateLua, playername.c_str());

		int error = lua_pcall(stateLua, 2, 1, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnPlayerConnecting");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}

		if (result == 1)
			result = (int)luaL_optinteger(stateLua, -1, 1);
	}
	lua_pop(stateLua, -1);

	return result;
}

extern "C" DLL_PUBLIC bool API_OnPlayerConnected(int entity)
{
	int result = 1;

	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onplayerconnected") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				Player ent;
				ent.entity = entity;
				push(stateLua, ent);

				int error = lua_pcall(stateLua, 1, 1, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}

				if (result == 1)
					result = (int)luaL_optinteger(stateLua, -1, 1);
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnPlayerConnected");
	if (lua_isfunction(stateLua, -1))
	{
		Player ent;
		ent.entity = entity;
		push(stateLua, ent);

		int error = lua_pcall(stateLua, 1, 1, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnPlayerConnected");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}

		if (result == 1)
			result = (int)luaL_optinteger(stateLua, -1, 1);
	}
	lua_pop(stateLua, -1);

	return result;
}

/// <param name="reason">The reason the player disconnected,  0 = Left, 1 = Timeout, 2 = Kicked, 3 = Banned</param>
extern "C" DLL_PUBLIC void API_OnPlayerDisconnected(int entity, int reason)
{
	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onplayerdisconnected") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				Player ent;
				ent.entity = entity;
				push(stateLua, ent);

				lua_pushinteger(stateLua, reason);

				int error = lua_pcall(stateLua, 2, 0, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnPlayerDisconnected");
	if (lua_isfunction(stateLua, -1))
	{
		Player ent;
		ent.entity = entity;
		push(stateLua, ent);

		lua_pushinteger(stateLua, reason);

		int error = lua_pcall(stateLua, 2, 0, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnPlayerDisconnected");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}
	}
	lua_pop(stateLua, -1);
}

extern "C" DLL_PUBLIC void API_OnEntityEnterCheckpoint(int checkpoint, int entity)
{
	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onentityentercheckpoint") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				Checkpoint cp;
				cp.entity = checkpoint;
				push(stateLua, cp);

				const int type = API::Entity::GetType(entity);
				switch (type) // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)
				{
				case 0: {
					Player ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 1: {
					Vehicle ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 2: {
					Object ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 3: {
					NPC ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				default:
					lua_pushnil(stateLua);
					break;
				}


				int error = lua_pcall(stateLua, 2, 0, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnEntityEnterCheckpoint");
	if (lua_isfunction(stateLua, -1))
	{
		Checkpoint cp;
		cp.entity = checkpoint;
		push(stateLua, cp);

		const int type = API::Entity::GetType(entity);
		switch (type) // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)
		{
		case 0: {
			Player ent;
			ent.entity = entity;
			push(stateLua, ent);
			break; 
		}
		case 1: {
			Vehicle ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 2: {
			Object ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 3: {
			NPC ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		default:
			lua_pushnil(stateLua);
			break;
		}

		int error = lua_pcall(stateLua, 2, 0, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnEntityEnterCheckpoint");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}
	}
	lua_pop(stateLua, -1);
}

extern "C" DLL_PUBLIC void API_OnEntityExitCheckpoint(int checkpoint, int entity)
{
	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onentityexitcheckpoint") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				Checkpoint cp;
				cp.entity = checkpoint;
				push(stateLua, cp);

				const int type = API::Entity::GetType(entity);
				switch (type) // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)
				{
				case 0: {
					Player ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 1: {
					Vehicle ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 2: {
					Object ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 3: {
					NPC ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				default:
					lua_pushnil(stateLua);
					break;
				}

				int error = lua_pcall(stateLua, 2, 0, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnEntityExitCheckpoint");
	if (lua_isfunction(stateLua, -1))
	{
		Checkpoint cp;
		cp.entity = checkpoint;
		push(stateLua, cp);

		const int type = API::Entity::GetType(entity);
		switch (type) // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)
		{
		case 0: {
			Player ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 1: {
			Vehicle ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 2: {
			Object ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 3: {
			NPC ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		default:
			lua_pushnil(stateLua);
			break;
		}

		int error = lua_pcall(stateLua, 2, 0, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnEntityExitCheckpoint");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}
	}
	lua_pop(stateLua, -1);
}

extern "C" DLL_PUBLIC void API_OnPlayerCommand(const int entity, const std::string message)
{
	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onplayercommand") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				Player ent;
				ent.entity = entity;
				push(stateLua, ent);

				lua_pushstring(stateLua, message.c_str());

				int error = lua_pcall(stateLua, 2, 0, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnPlayerCommand");
	if (lua_isfunction(stateLua, -1))
	{
		Player ent;
		ent.entity = entity;
		push(stateLua, ent);

		lua_pushstring(stateLua, message.c_str());

		int error = lua_pcall(stateLua, 2, 0, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnPlayerCommand");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}
	}
	lua_pop(stateLua, -1);
}

extern "C" DLL_PUBLIC void API_OnPlayerMessage(const int entity, const std::string message)
{
	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onplayermessage") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				Player ent;
				ent.entity = entity;
				push(stateLua, ent);

				lua_pushstring(stateLua, message.c_str());

				int error = lua_pcall(stateLua, 2, 0, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnPlayerMessage");
	if (lua_isfunction(stateLua, -1))
	{
		Player ent;
		ent.entity = entity;
		push(stateLua, ent);

		lua_pushstring(stateLua, message.c_str());

		int error = lua_pcall(stateLua, 2, 0, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnPlayerMessage");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}
	}

	lua_pop(stateLua, -1);
}

// Called whern a player has just shot
extern "C" DLL_PUBLIC void API_OnPlayerShot(const int entity, const std::string weapon)
{
	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onplayershot") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				Player ent;
				ent.entity = entity;
				push(stateLua, ent);

				lua_pushstring(stateLua, weapon.c_str());

				int error = lua_pcall(stateLua, 2, 0, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnPlayerShot");
	if (lua_isfunction(stateLua, -1))
	{
		Player ent;
		ent.entity = entity;
		push(stateLua, ent);

		lua_pushstring(stateLua, weapon.c_str());

		int error = lua_pcall(stateLua, 2, 0, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnPlayerShot");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}
	}

	lua_pop(stateLua, -1);
}

// Called whern a entity has taken damage
extern "C" DLL_PUBLIC const bool API_OnEntityDamage(const int entity, const int damage, const int attacker, const std::string weapon)
{
	int result = 1;

	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onentitydamage") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				int type = API::Entity::GetType(entity);
				switch (type) // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)
				{
				case 0: {
					Player ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 1: {
					Vehicle ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 2: {
					Object ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 3: {
					NPC ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				default:
					lua_pushnil(stateLua);
					break;
				}

				lua_pushinteger(stateLua, damage);
				
				type = API::Entity::GetType(attacker);
				switch (type) // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)
				{
				case 0: {
					Player ent;
					ent.entity = attacker;
					push(stateLua, ent);
					break;
				}
				case 3: {
					NPC ent;
					ent.entity = attacker;
					push(stateLua, ent);
					break;
				}
				default:
					lua_pushnil(stateLua);
					break;
				}

				lua_pushstring(stateLua, weapon.c_str());

				int error = lua_pcall(stateLua, 4, 1, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}

				if(result == 1)
					result = (int)luaL_optinteger(stateLua, -1, 1);
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnEntityDamage");
	if (lua_isfunction(stateLua, -1))
	{
		int type = API::Entity::GetType(entity);
		switch (type) // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)
		{
		case 0: {
			Player ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 1: {
			Vehicle ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 2: {
			Object ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 3: {
			NPC ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		default:
			lua_pushnil(stateLua);
			break;
		}

		lua_pushinteger(stateLua, damage);

		type = API::Entity::GetType(attacker);
		switch (type) // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)
		{
		case 0: {
			Player ent;
			ent.entity = attacker;
			push(stateLua, ent);
			break;
		}
		case 3: {
			NPC ent;
			ent.entity = attacker;
			push(stateLua, ent);
			break;
		}
		default:
			lua_pushnil(stateLua);
			break;
		}

		lua_pushstring(stateLua, weapon.c_str());

		int error = lua_pcall(stateLua, 4, 1, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnEntityDamage");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}

		if (result == 1)
			result = (int)luaL_optinteger(stateLua, -1, 1);
	}

	lua_pop(stateLua, -1);
	return result;
}

// Called after a player has shot and their projectile hits something
extern "C" DLL_PUBLIC void API_OnProjectileImpact(const int player, const std::string weapon, CVector3 position, const int entity, const int bone)
{
	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onprojectileimpact") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				Player p;
				p.entity = player;
				push(stateLua, p);

				lua_pushstring(stateLua, weapon.c_str());

				lua_newtable(stateLua);
				lua_pushinteger(stateLua, position.x);
				lua_setfield(stateLua, -2, "x");
				lua_pushinteger(stateLua, position.y);
				lua_setfield(stateLua, -2, "y");
				lua_pushinteger(stateLua, position.z);
				lua_setfield(stateLua, -2, "z");

				const int type = API::Entity::GetType(entity);
				switch (type) // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)
				{
				case 0: {
					Player ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 1: {
					Vehicle ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 2: {
					Object ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 3: {
					NPC ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 4: {
					Checkpoint ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 5: {
					Blip ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				default:
					lua_pushnil(stateLua);
					break;
				}

				lua_pushinteger(stateLua, bone);

				int error = lua_pcall(stateLua, 5, 0, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnProjectileImpact");
	if (lua_isfunction(stateLua, -1))
	{
		Player p;
		p.entity = player;
		push(stateLua, p);

		lua_pushstring(stateLua, weapon.c_str());

		lua_newtable(stateLua);
		lua_pushinteger(stateLua, position.x);
		lua_setfield(stateLua, -2, "x");
		lua_pushinteger(stateLua, position.y);
		lua_setfield(stateLua, -2, "y");
		lua_pushinteger(stateLua, position.z);
		lua_setfield(stateLua, -2, "z");

		const int type = API::Entity::GetType(entity);
		switch (type) // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)
		{
		case 0: {
			Player ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 1: {
			Vehicle ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 2: {
			Object ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 3: {
			NPC ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 4: {
			Checkpoint ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 5: {
			Blip ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		default:
			lua_pushnil(stateLua);
			break;
		}

		lua_pushinteger(stateLua, bone);

		int error = lua_pcall(stateLua, 5, 0, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnProjectileImpact");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}
	}
	lua_pop(stateLua, -1);
}

// Called when a player picks up and pickup
extern "C" DLL_PUBLIC void API_OnPlayerPickup(const int player, const int pickup)
{
	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onplayerpickup") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				Player ent;
				ent.entity = player;
				push(stateLua, ent);

				Pickup pick;
				pick.entity = pickup;
				push(stateLua, pick);

				int error = lua_pcall(stateLua, 2, 0, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnPlayerPickup");
	if (lua_isfunction(stateLua, -1))
	{
		Player ent;
		ent.entity = player;
		push(stateLua, ent);

		Pickup pick;
		pick.entity = pickup;
		push(stateLua, pick);

		int error = lua_pcall(stateLua, 2, 0, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnPlayerPickup");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}
	}

	lua_pop(stateLua, -1);
}

// When a CEF page has finished loading
extern "C" DLL_PUBLIC void API_OnCefFinishLoad(const int player)
{
	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onceffinishload") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				Player ent;
				ent.entity = player;
				push(stateLua, ent);

				int error = lua_pcall(stateLua, 1, 0, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnCefFinishLoad");
	if (lua_isfunction(stateLua, -1))
	{
		Player ent;
		ent.entity = player;
		push(stateLua, ent);

		int error = lua_pcall(stateLua, 1, 0, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnCefFinishLoad");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}
	}

	lua_pop(stateLua, -1);
}

// When a CEF page sends data
extern "C" DLL_PUBLIC void API_OnCefSendData(const int player, const std::string data)
{
	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("oncefsenddata") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				Player ent;
				ent.entity = player;
				push(stateLua, ent);

				lua_pushstring(stateLua, data.c_str());

				int error = lua_pcall(stateLua, 2, 0, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnCefSendData");
	if (lua_isfunction(stateLua, -1))
	{
		Player ent;
		ent.entity = player;
		push(stateLua, ent);

		lua_pushstring(stateLua, data.c_str());

		int error = lua_pcall(stateLua, 2, 0, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnCefSendData");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}
	}

	lua_pop(stateLua, -1);
}

// Called when an entity dies
extern "C" DLL_PUBLIC void API_OnEntityDeath(const int entity, const int killer)
{
	// Events
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i].evt.compare("onentitydeath") == 0)
		{
			lua_rawgeti(stateLua, LUA_REGISTRYINDEX, events[i].functionKey);
			if (lua_isfunction(stateLua, -1))
			{
				int type = API::Entity::GetType(entity);
				switch (type)
				{
				case 0: {
					Player ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 1: {
					Vehicle ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 2: {
					Object ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				case 3: {
					NPC ent;
					ent.entity = entity;
					push(stateLua, ent);
					break;
				}
				default:
					lua_pushnil(stateLua);
					break;
				}

				type = API::Entity::GetType(killer);
				switch (type)
				{
				case 0: {
					Player ent;
					ent.entity = killer;
					push(stateLua, ent);
					break;
				}
				case 1: {
					Vehicle ent;
					ent.entity = killer;
					push(stateLua, ent);
					break;
				}
				case 2: {
					Object ent;
					ent.entity = killer;
					push(stateLua, ent);
					break;
				}
				case 3: {
					NPC ent;
					ent.entity = killer;
					push(stateLua, ent);
					break;
				}
				default:
					lua_pushnil(stateLua);
					break;
				}

				int error = lua_pcall(stateLua, 2, 0, 0);
				if (error != 0)
				{
					std::stringstream str;
					str << "Error: %s" << lua_tostring(stateLua, -1);
					API::Log::Error(str.str());
				}
			}
			lua_pop(stateLua, 1);
		}
	}
	// END Events

	lua_getglobal(stateLua, "OnEntityDeath");
	if (lua_isfunction(stateLua, -1))
	{
		int type = API::Entity::GetType(entity);
		switch (type)
		{
		case 0: {
			Player ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 1: {
			Vehicle ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 2: {
			Object ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		case 3: {
			NPC ent;
			ent.entity = entity;
			push(stateLua, ent);
			break;
		}
		default:
			lua_pushnil(stateLua);
			break;
		}

		type = API::Entity::GetType(killer);
		switch (type)
		{
		case 0: {
			Player ent;
			ent.entity = killer;
			push(stateLua, ent);
			break;
		}
		case 1: {
			Vehicle ent;
			ent.entity = killer;
			push(stateLua, ent);
			break;
		}
		case 2: {
			Object ent;
			ent.entity = killer;
			push(stateLua, ent);
			break;
		}
		case 3: {
			NPC ent;
			ent.entity = killer;
			push(stateLua, ent);
			break;
		}
		default:
			lua_pushnil(stateLua);
			break;
		}

		int error = lua_pcall(stateLua, 2, 0, 0);
		if (error != 0)
		{
			API::Log::Error("Error occured when executing OnEntityDeath");
			std::stringstream str;
			str << "Error: %s" << lua_tostring(stateLua, -1);
			API::Log::Error(str.str());
		}
	}

	lua_pop(stateLua, -1);
}

#pragma endregion