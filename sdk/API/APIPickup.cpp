#include "APIPickup.h"

namespace API
{
	namespace Pickup
	{
		Objects::Entity Create(const CVector3 position, std::string model)
		{
			return CreatePickup(position, model);
		}

		void Show(Objects::Entity entity, Objects::Entity playerEntity)
		{
			ShowPickup(entity, playerEntity);
		}

		void Hide(Objects::Entity entity, Objects::Entity playerEntity)
		{
			HidePickup(entity, playerEntity);
		}

		std::string GetModel(Objects::Entity entity)
		{
			return GetPickupModel(entity);
		}

		void SetModel(Objects::Entity entity, const std::string model)
		{
			SetPickupModel(entity, model);
		}

		const int GetRespawnDelay(Objects::Entity entity)
		{
			return GetPickupRespawnDelay(entity);
		}

		void SetRespawnDelay(Objects::Entity entity, const int time)
		{
			SetPickupRespawnDelay(entity, time);
		}
	}
}