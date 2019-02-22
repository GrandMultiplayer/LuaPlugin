#ifndef __NPC_H__
#define __NPC_H__

class NPC : public CEntity
{
public:
	NPC() {}

	NPC(const std::string model, const CVector3 position, const CVector3 rotation) { *this = API::NPC::Create(model, position, rotation); }

	/// <summary>
	/// Assign CEntity
	/// </summary>
	/// <param name="e">CEntity to assign from</param>
	/// <returns>Itself</returns>
	NPC &operator=(const CEntity &e)
	{
		identity.entityId = const_cast<CEntity&>(e).GetID();
		identity.type = const_cast<CEntity&>(e).GetType();
		return (*this);
	}

	void Destroy()
	{
		API::Entity::Destroy(*this);
		identity.entityId = -1;
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

	void ShowBlip(CEntity player)
	{
		API::Blip::Show(*this, player);
	}

	void HideBlip(CEntity player)
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

	void Revive()
	{
		API::Entity::Revive(*this);
	}

	const bool IsAlive()
	{
		return API::Entity::IsAlive(*this);
	}
};

#endif