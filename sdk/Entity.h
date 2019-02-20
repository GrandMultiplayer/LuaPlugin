#ifndef __ENTITY_H__
#define __ENTITY_H__

namespace GrandM
{
	enum EntityType
	{
		Nill = -1,
		Player,
		NPC,
		Vehicle,
		Object,
		Checkpoint,
		Pickup,
		Blip,
	};
}

namespace Objects
{
	class DLL_PUBLIC_I Entity
	{
	protected:
		int	entityId = -1;
		GrandM::EntityType type = GrandM::EntityType::Nill;

	public:
		void SetID(const int i) { entityId = i; }
		const int GetID() { return entityId; }
		void SetType(const GrandM::EntityType t) { type = t; }
		const GrandM::EntityType GetType() { return type; }

		Entity() {}
		~Entity() {}
	
		/// <summary>
		/// Copy constructors
		/// </summary>
		/// <param name="v">Entity to assign from</param>
		Entity(const Entity &e)
		{
			entityId = e.entityId;
			type = e.type;
		}

		/// <summary>
		/// Assign Entity
		/// </summary>
		/// <param name="v">Entity to assign from</param>
		/// <returns>Itself</returns>
		Entity &operator=(const Entity &e)
		{
			entityId = e.entityId;
			type = e.type;
			return (*this);
		}
	};
}
#endif