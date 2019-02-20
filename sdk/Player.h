#ifndef __PLAYER_H__
#define __PLAYER_H__

class CPlayer : public Objects::Entity
{
public:
	CPlayer() {}

	/// <summary>
	/// Assign CEntity
	/// </summary>
	/// <param name="e">CEntity to assign from</param>
	/// <returns>Itself</returns>
	CPlayer &operator=(const Objects::Entity &e)
	{
		entityId = const_cast<Objects::Entity&>(e).GetID();
		type = const_cast<Objects::Entity&>(e).GetType();
		return (*this);
	}

	const bool operator==(Objects::Entity &e)
	{
		return e.GetID() == entityId;
	}

	const bool operator!=(Objects::Entity &e)
	{
		return e.GetID() != entityId;
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

	const GrandM::Model::Component GetPedComponent(const int componentid)
	{
		return API::Entity::GetPedComponent(*this, componentid);
	}

	void SetPedComponent(const int componentid, const GrandM::Model::Component component)
	{
		API::Entity::SetPedComponent(*this, componentid, component);
	}

	const GrandM::Model::HeadBlend GetPedHeadBlend()
	{
		return API::Entity::GetPedHeadBlend(*this);
	}

	void SetPedHeadBlend(const GrandM::Model::HeadBlend headblend)
	{
		API::Entity::SetPedHeadBlend(*this, headblend);
	}

	const GrandM::Model::HeadOverlay GetPedHeadOverlay(const int overlayid)
	{
		return API::Entity::GetPedHeadOverlay(*this, overlayid);
	}

	void SetPedHeadOverlay(const int overlayid, const GrandM::Model::HeadOverlay overlay)
	{
		API::Entity::SetPedHeadOverlay(*this, overlayid, overlay);
	}

	const GrandM::Model::Prop GetPedProp(const int compotentid)
	{
		return API::Entity::GetPedProp(*this, compotentid);
	}

	void SetPedProp(const int compotentid, const GrandM::Model::Prop prop)
	{
		API::Entity::SetPedProp(*this, compotentid, prop);
	}

	const float GetPedFaceFeature(const int index)
	{
		return API::Entity::GetPedFaceFeature(*this, index);
	}

	void SetPedFaceFeature(const int index, const float scale)
	{
		API::Entity::SetPedFaceFeature(*this, index, scale);
	}

	const float GetViewDistance()
	{
		return API::Entity::GetViewDistance(*this);
	}

	void SetViewDistance(const float distance)
	{
		API::Entity::SetViewDistance(*this, distance);
	}

	const std::string GetModel()
	{
		return API::Player::GetPlayerModel(*this);
	}

	void SetModel(const std::string model)
	{
		API::Player::SetPlayerModel(*this, model);
	}

	void ShowNotification(const std::string message, const std::string pic, const int icontype, const int color, const std::string sender, const std::string subject)
	{
		API::Visual::ShowNotificationToPlayer(*this, message, pic, icontype, color, sender, subject);
	}

	void ShowSubtitle(const std::string message, const int duration, const bool shownow)
	{
		API::Visual::ShowSubtitleToPlayer(*this, message, duration, shownow);
	}

	void SendChatMessage(const std::string message)
	{
		API::Visual::SendChatMessageToPlayer(*this, message);
	}

	const std::string GetUsername()
	{
		return API::Player::GetUsername(*this);
	}

	void SetUsername(const std::string name)
	{
		API::Player::SetUsername(*this, name);
	}

	void ShowCursor(const bool show)
	{
		API::Visual::ShowCursor(*this, show);
	}
	
	void LoadURL(std::string frame, std::string url, std::string appcode = "", bool remote = false)
	{
		API::CEF::LoadURL(*this, frame, url, appcode, remote);
	}

	void JavaScriptCall(std::string frame, std::string call)
	{
		API::CEF::ExecuteJavaScript(*this, frame, call);
	}

	const bool IsControllable()
	{
		return API::Player::IsControllable(*this);
	}

	void SetControllable(bool disablecontrols, bool frozen = false)
	{
		API::Player::SetControllable(*this, disablecontrols, frozen);
	}

	const std::string GetIP(const int entity)
	{
		return API::Player::GetIP(*this);
	}

	const std::string GetSecretKey(const int entity)
	{
		return API::Player::GetSecretKey(*this);
	}

	void Kick(const std::string reason)
	{
		API::Player::Kick(*this, reason);
	}

	void PutInVehicle(Objects::Entity vehicleEntity, const int seat)
	{
		API::Player::PutInVehicle(*this, vehicleEntity, seat);
	}

	Objects::Entity GetVehicle()
	{
		return API::Player::GetVehicle(*this);
	}

	const int GetSeat()
	{
		return API::Player::GetSeat(*this);
	}

	void GiveWeapon(const std::string weapon, const int ammo = 0)
	{
		API::Player::GiveWeapon(*this, weapon, ammo);
	}

	void RemoveWeapon(const std::string weapon)
	{
		API::Player::RemoveWeapon(*this, weapon);
	}

	const std::string GetNametag()
	{
		return API::Entity::GetNametag(*this);
	}

	void SetNametag(const std::string nametag)
	{
		API::Entity::SetNametag(*this, nametag);
	}

	const bool IsNametagVisible()
	{
		return API::Entity::IsNametagVisible(*this);
	}

	void SetNametagVisible(const bool visible)
	{
		API::Entity::SetNametagVisible(*this, visible);
	}

	const bool IsHealthbarVisible()
	{
		return API::Entity::IsHealthbarVisible(*this);
	}

	void SetHealthbarVisible(const bool visible)
	{
		API::Entity::SetHealthbarVisible(*this, visible);
	}

	const float GetNametagDistance()
	{
		return API::Entity::GetNametagDistance(*this);
	}

	void SetNametagDistance(const float distance)
	{
		API::Entity::SetNametagDistance(*this, distance);
	}

	const Color GetNametagColor()
	{
		return API::Entity::GetNametagColor(*this);
	}

	void SetNametagColor(const Color color)
	{
		API::Entity::SetNametagColor(*this, color);
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

	const std::string GetText()
	{
		return API::Blip::GetText(*this);
	}

	void SetText(const std::string text)
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

	void SetBlackout(const bool state)
	{
		API::World::SetBlackoutForPlayer(*this, state);
	}

	void SetGroundSnow(const bool state)
	{
		API::World::SetGroundSnowForPlayer(*this, state);
	}

	void GetWeaponAmmo(const std::string weapon, int* ammo, int* clipAmmo)
	{
		API::Player::GetWeaponAmmo(*this, weapon, ammo, clipAmmo);
	}

	void SetWeaponAmmo(const std::string weapon, int ammo, int clipAmmo)
	{
		API::Player::SetWeaponAmmo(*this, weapon, ammo, clipAmmo);
	}

	std::string * GetWeapons()
	{
		return API::Player::GetWeapons(*this);
	}

	void EquipWeapon(const std::string weapon)
	{
		API::Player::EquipWeapon(*this, weapon);
	}

	const int GetHealth()
	{
		return API::Entity::GetHealth(*this);
	}

	void SetHealth(const int health)
	{
		API::Entity::SetHealth(*this, health);
	}

	const int GetArmour()
	{
		return API::Entity::GetArmour(*this);
	}

	void SetArmour(const int armour)
	{
		API::Entity::SetArmour(*this, armour);
	}

	const bool IsHudHidden()
	{
		return API::Visual::IsHudHidden(*this);
	}

	void DisplayHud(const bool show)
	{
		API::Visual::DisplayHud(*this, show);
	}

	const bool IsRadarHidden()
	{
		return API::Visual::IsRadarHidden(*this);
	}

	void DisplayRadar(const bool show)
	{
		API::Visual::DisplayRadar(*this, show);
	}

	const bool IsCashHidden()
	{
		return API::Visual::IsCashHidden(*this);
	}

	void DisplayCash(const bool show)
	{
		API::Visual::DisplayCash(*this, show);
	}

	const bool IsAmmoHidden()
	{
		return API::Visual::IsAmmoHidden(*this);
	}

	void DisplayAmmo(const bool show)
	{
		API::Visual::DisplayAmmo(*this, show);
	}

	void Revive()
	{
		API::Entity::Revive(*this);
	}

	const bool IsAlive()
	{
		return API::Entity::IsAlive(*this);
	}

	void SetCameraPosition(const CVector3 position)
	{
		API::Camera::SetPosition(*this, position);
	}

	void SetCameraRotation(const CVector3 rotation)
	{
		API::Camera::SetRotation(*this, rotation);
	}

	void ResetCamera()
	{
		API::Camera::Reset(*this);
	}

	void FirstPersonOnly()
	{
		API::Camera::FirstPersonOnly(*this);
	}

	void ThirdPersonOnly()
	{
		API::Camera::ThirdPersonOnly(*this);
	}

	void AttachCamera(Objects::Entity entity, const CVector3 offset)
	{
		API::Camera::Attach(*this, entity, offset);
	}

	void DetachCamera()
	{
		API::Camera::Detach(*this);
	}

	const bool IsCameraActive()
	{
		API::Camera::IsActive(*this);
	}
};

#endif