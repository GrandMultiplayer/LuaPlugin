#ifndef __PICKUP_H__
#define __PICKUP_H__

class Pickup : public CEntity
{
public:
	Pickup() {}
	Pickup(const CVector3 position, std::string model = "prop_beach_volball02") { *this = API::Pickup::Create(position, model); }

	/// <summary>
	/// Assign CEntity
	/// </summary>
	/// <param name="e">CEntity to assign from</param>
	/// <returns>Itself</returns>
	Pickup &operator=(const CEntity &e)
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

	const float GetViewDistance()
	{
		return API::Entity::GetViewDistance(*this);
	}

	void SetViewDistance(const float distance)
	{
		API::Entity::SetViewDistance(*this, distance);
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

	const std::string GetBlipText()
	{
		return API::Blip::GetText(*this);
	}

	void SetBLipText(const std::string text)
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

	void ShowToAll()
	{
		API::Pickup::ShowToAll(*this);
	}

	void HideFromAll()
	{
		API::Pickup::HideFromAll(*this);
	}

	void Show(CEntity playerEntity)
	{
		API::Pickup::Show(*this, playerEntity);
	}

	void Hide(CEntity playerEntity)
	{
		API::Pickup::Hide(*this, playerEntity);
	}

	std::string GetModel()
	{
		return API::Pickup::GetModel(*this);
	}

	void SetModel(const std::string model)
	{
		API::Pickup::SetModel(*this, model);
	}

	const int GetRespawnDelay()
	{
		return API::Pickup::GetRespawnDelay(*this);
	}

	void SetRespawnDelay(const int time)
	{
		API::Pickup::SetRespawnDelay(*this, time);
	}
};

#endif