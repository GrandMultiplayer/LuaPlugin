#ifndef __CHECKPOINT_H__
#define __CHECKPOINT_H__

class Checkpoint : public CEntity
{
public:
	Checkpoint() {}
	Checkpoint(const CVector3 position, const float radius, const Color color, const int reserved) { *this = API::Checkpoint::Create(position, radius, color, reserved); }

	/// <summary>
	/// Assign CEntity
	/// </summary>
	/// <param name="e">CEntity to assign from</param>
	/// <returns>Itself</returns>
	Checkpoint &operator=(const CEntity &e)
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

	void Show(CEntity playerentity)
	{
		API::Checkpoint::Show(*this, playerentity);
	}

	void Hide(CEntity playerentity)
	{
		API::Checkpoint::Hide(*this, playerentity);
	}

	const float GetNearHeight()
	{
		return API::Checkpoint::GetNearHeight(*this);
	}

	void SetFarHeight(const float height)
	{
		API::Checkpoint::SetFarHeight(*this, height);
	}

	const float GetFarHeight()
	{
		return API::Checkpoint::GetFarHeight(*this);
	}

	void SetNearHeight(const float height)
	{
		API::Checkpoint::SetNearHeight(*this, height);
	}

	const float GetViewDistance()
	{
		return API::Entity::GetViewDistance(*this);
	}

	void SetViewDistance(const float distance)
	{
		API::Entity::SetViewDistance(*this, distance);
	}

	const CVector3 GetPointTo()
	{
		return API::Checkpoint::GetPointTo(*this);
	}

	void PointTo(const CVector3 pointTo)
	{
		API::Checkpoint::PointTo(*this, pointTo);
	}

	const int GetType()
	{
		return API::Checkpoint::GetType(*this);
	}

	void SetType(const int type)
	{
		API::Checkpoint::SetType(*this, type);
	}

	const Color GetColor()
	{
		return API::Checkpoint::GetColor(*this);
	}

	void SetColor(const Color color)
	{
		API::Checkpoint::SetColor(*this, color);
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
};

#endif