#ifndef __VEHICLE_H__
#define __VEHICLE_H__
#include "API/APIVehicle.h"

class CVehicle : public Objects::Entity
{
public:
	CVehicle() {}
	CVehicle(const char* model, const CVector3 position, const float heading) { *this = API::Vehicle::Create(model, position, heading); }
	CVehicle(const char* model, const CVector3 position, const CVector3 rotation) { *this = API::Vehicle::Create(model, position, rotation); }

	~CVehicle() {}

	/// <summary>
	/// Assign CEntity
	/// </summary>
	/// <param name="e">CEntity to assign from</param>
	/// <returns>Itself</returns>
	CVehicle& operator=(Objects::Entity&& e)
	{
		if (this != &e) {
			entityId = const_cast<Objects::Entity&>(e).GetID();
			type = const_cast<Objects::Entity&>(e).GetType();
		}
		return (*this);
	}

	void Destroy()
	{
		API::Entity::Destroy(*this);
		entityId = -1;
	}

	const CVector3 GetPosition()
	{
		return API::Entity::GetPosition(*this);
	}

	void SetPosition(const CVector3 position)
	{
		API::Entity::SetPosition(*this, position);
	}

	const CVector3 GetRotation()
	{
		return API::Entity::GetRotation(*this);
	}

	void SetRotation(const CVector3 position)
	{
		API::Entity::SetRotation(*this, position);
	}

	const float GetViewDistance()
	{
		return API::Entity::GetViewDistance(*this);
	}

	void SetViewDistance(const float distance)
	{
		API::Entity::SetViewDistance(*this, distance);
	}

	const int GetColor(const int layer)
	{
		return API::Vehicle::GetVehicleColor(*this, layer);
	}

	const int GetColorType(const int layer)
	{
		return API::Vehicle::GetVehicleColorType(*this, layer);
	}

	const Color GetCustomColor(const int layer)
	{
		return API::Vehicle::GetVehicleRGBColor(*this, layer);
	}

	void SetColor(const int layer, const int painttype, const int color)
	{
		API::Vehicle::SetVehicleColor(*this, layer, painttype, color);
	}

	void SetColor(const int layer, const Color color)
	{
		API::Vehicle::SetVehicleRGBColor(*this, layer, color);
	}

	const std::string GetNumberPlate()
	{
		return API::Vehicle::GetNumberPlate(*this);
	}

	void SetNumberPlate(const std::string plate)
	{
		API::Vehicle::SetNumberPlate(*this, plate);
	}

	const int GetMod(const int modType)
	{
		return API::Vehicle::GetMod(*this, modType);
	}

	void SetMod(const int modType, const int modIndex)
	{
		API::Vehicle::SetMod(*this, modType, modIndex);
	}

	const bool GetEngineState()
	{
		return API::Vehicle::GetEngineState(*this);
	}

	void SetEngineState(const bool state, const bool instant)
	{
		API::Vehicle::SetEngineState(*this, state, instant);
	}

	const int GetDoorsLockState()
	{
		return API::Vehicle::GetDoorsLockState(*this);
	}

	void SetDoorsLockState(const int state)
	{
		API::Vehicle::SetDoorsLockState(*this, state);
	}

	void SetDoorsLockState(const int state, Objects::Entity player)
	{
		API::Vehicle::SetDoorsLockStateForPlayer(*this, state, player);
	}

	const std::string GetModel()
	{
		return API::Vehicle::GetVehicleModel(*this);
	}

	const int GetNumberPlateStyle()
	{
		return API::Vehicle::GetNumberPlateStyle(*this);
	}

	void SetNumberPlateStyle(const int style)
	{
		API::Vehicle::SetNumberPlateStyle(*this, style);
	}

	const bool GetExtra(const int extra)
	{
		return API::Vehicle::GetExtra(*this, extra);
	}

	void SetExtra(const int extra, const bool toggle)
	{
		return API::Vehicle::SetExtra(*this, extra, toggle);
	}

	const float GetEngineHealth()
	{
		return API::Vehicle::GetEngineHealth(*this);
	}

	void SetEngineHealth(const float health)
	{
		API::Vehicle::SetEngineHealth(*this, health);
	}

	const float GetFuelTankHealth()
	{
		return API::Vehicle::GetFuelTankHealth(*this);
	}

	void SetFuelTankHealth(const float health)
	{
		API::Vehicle::SetFuelTankHealth(*this, health);
	}

	void FixDeformation()
	{
		API::Vehicle::FixDeformation(*this);
	}

	Objects::Entity GetOccupant(const int seat)
	{
		return API::Vehicle::GetOccupant(*this, seat);
	}

	Objects::Entity * GetOccupants()
	{
		return API::Vehicle::GetOccupants(*this);
	}

	const bool GetTaxiLightState()
	{
		return API::Vehicle::GetTaxiLightState(*this);
	}

	void SetTaxiLightState(const bool state)
	{
		API::Vehicle::SetTaxiLightState(*this, state);
	}

	const bool GetIndicatorState(const int turnlight)
	{
		return API::Vehicle::GetIndicatorState(*this, turnlight);
	}

	void SetIndicatorState(const int turnlight, const bool state)
	{
		API::Vehicle::SetIndicatorState(*this, turnlight, state);
	}

	const bool GetInteriorLightState()
	{
		return API::Vehicle::GetInteriorLightState(*this);
	}

	void SetInteriorLightState(const bool state)
	{
		API::Vehicle::SetInteriorLightState(*this, state);
	}

	const bool GetSirenSoundState()
	{
		return API::Vehicle::GetSirenSoundState(*this);
	}

	void SetSirenSoundState(const bool state)
	{
		API::Vehicle::SetSirenSoundState(*this, state);
	}

	void CreateBlip()
	{
		API::Blip::Create(*this);
	}

	void ShowBlip(Objects::Entity player)
	{
		API::Blip::Show(*this, player);
	}

	void HideBlip(Objects::Entity player)
	{
		API::Blip::Hide(*this, player);
	}

	void ShowBlipToAll()
	{
		API::Blip::ShowToAll(*this);
	}

	void HideBlipFromAll()
	{
		API::Blip::HideFromAll(*this);
	}

	const int GetBlipColor()
	{
		return API::Blip::GetColor(*this);
	}

	void SetBlipColor(const int color)
	{
		API::Blip::SetColor(*this, color);
	}

	const int GetBlipSprite()
	{
		return API::Blip::GetSprite(*this);
	}

	void SetBlipSprite(const int sprite)
	{
		API::Blip::SetSprite(*this, sprite);
	}

	const std::string GetBlipText()
	{
		return API::Blip::GetText(*this);
	}

	void SetBlipText(const std::string text)
	{
		API::Blip::SetText(*this, text);
	}

	const bool IsBlipShortRanged()
	{
		return API::Blip::IsShortRanged(*this);
	}

	void SetBlipShortRanged(const bool state)
	{
		API::Blip::SetShortRanged(*this, state);
	}

	const int GetHealth()
	{
		return API::Entity::GetHealth(*this);
	}

	void SetHealth(const int health)
	{
		API::Entity::SetHealth(*this, health);
	}

	const bool IsAlive()
	{
		return API::Entity::IsAlive(*this);
	}

	Objects::Entity GetTowedVehicle()
	{
		return API::Vehicle::GetTowedVehicle(*this);
	}

	void SetTowedVehicle(Objects::Entity entity)
	{
		API::Vehicle::SetTowedVehicle(*this, entity);
	}

	const bool IsTowed()
	{
		return API::Vehicle::IsTowed(*this);
	}
};
extern std::vector<CVehicle> vehicles;
#endif