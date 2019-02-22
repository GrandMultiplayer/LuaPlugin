#ifndef __OBJECT_H__
#define __OBJECT_H__

class Object : public CEntity
{
public:
	Object() {}
	Object(const std::string model, const CVector3 position, const CVector3 rotation, const bool dynamic) { *this = API::Object::Create(model, position, rotation, dynamic); }
	Object(const int hash, const CVector3 position, const CVector3 rotation, const bool dynamic) { *this = API::Object::Create(hash, position, rotation, dynamic); }

	/// <summary>
	/// Assign CEntity
	/// </summary>
	/// <param name="e">CEntity to assign from</param>
	/// <returns>Itself</returns>
	Object &operator=(const CEntity &e)
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

	const float GetViewDistance()
	{
		return API::Entity::GetViewDistance(*this);
	}

	void SetViewDistance(const float distance)
	{
		API::Entity::SetViewDistance(*this, distance);
	}

	const int GetTextureVariation()
	{
		return API::Object::GetTextureVariation(*this);
	}

	void SetTextureVariation(const int textureindex)
	{
		API::Object::SetTextureVariation(*this, textureindex);
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

	const bool IsAlive()
	{
		return API::Entity::IsAlive(*this);
	}
};

#endif