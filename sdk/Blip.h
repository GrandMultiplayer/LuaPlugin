#ifndef __BLIP_H__
#define __BLIP_H__

class Blip : public CEntity
{
public:
	Blip() {}
	Blip(CVector3 position) { *this = API::Blip::Create(position); }

	/// <summary>
	/// Assign CEntity
	/// </summary>
	/// <param name="e">CEntity to assign from</param>
	/// <returns>Itself</returns>
	Blip &operator=(const CEntity &e)
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

	void Show(CEntity player)
	{
		API::Blip::Show(*this, player);
	}

	void Hide(CEntity player)
	{
		API::Blip::Hide(*this, player);
	}

	void ShowToAll()
	{
		API::Blip::ShowToAll(*this);
	}

	void HideFromAll()
	{
		API::Blip::HideFromAll(*this);
	}

	const int GetColor()
	{
		return API::Blip::GetColor(*this);
	}

	void SetColor(const int color)
	{
		API::Blip::SetColor(*this, color);
	}

	const int GetSprite()
	{
		return API::Blip::GetSprite(*this);
	}

	void SetSprite(const int sprite)
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

	const bool IsShortRanged()
	{
		return API::Blip::IsShortRanged(*this);
	}

	void SetShortRanged(const bool state)
	{
		API::Blip::SetShortRanged(*this, state);
	}
};

#endif