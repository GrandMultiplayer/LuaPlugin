#ifndef __APIPICKUP_H__
#define __APIPICKUP_H__

DLL_PUBLIC_I_C Objects::Entity CreatePickup(const CVector3 position, std::string model = "prop_beach_volball02");
DLL_PUBLIC_I_C void ShowPickup(Objects::Entity entity, Objects::Entity playerEntity);
DLL_PUBLIC_I_C void HidePickup(Objects::Entity entity, Objects::Entity playerEntity);
DLL_PUBLIC_I_C std::string GetPickupModel(Objects::Entity entity);
DLL_PUBLIC_I_C void SetPickupModel(Objects::Entity entity, const std::string model);
DLL_PUBLIC_I_C const int GetPickupRespawnDelay(Objects::Entity entity);
DLL_PUBLIC_I_C void SetPickupRespawnDelay(Objects::Entity entity, const int time);

namespace API
{
	namespace Pickup
	{
		/// <summary>
		/// Creates a new pickup
		/// </summary>
		/// <param name="position">The position the pickup should be at.</param>
		/// <param name="model">The model you want the pickup to display as.</param>
		/// <returns name="entity">The pickups entity.</returns>
		Objects::Entity Create(const CVector3 position, std::string model = "prop_beach_volball02")
		{
			return CreatePickup(position, model);
		}

		/// <summary>
		/// Shows the pickup to the desired player.
		/// </summary>
		/// <param name="entity">The entity of the pickup you wish to show.</param>
		/// <param name="playerEntity">The entity of the player you wish to show the pickup too.</param>
		void Show(Objects::Entity entity, Objects::Entity playerEntity)
		{
			ShowPickup(entity, playerEntity);
		}

		/// <summary>
		/// Hides the pickup from the desired player.
		/// </summary>
		/// <param name="entity">The entity of the pickup you wish to hide.</param>
		/// <param name="playerEntity">The entity of the player you wish to hide the pickup from.</param>
		void Hide(Objects::Entity entity, Objects::Entity playerEntity)
		{
			HidePickup(entity, playerEntity);
		}

		/// <summary>
		/// Gets the pickups current model
		/// </summary>
		/// <param name="entity">The entity of the pickup you wish to get the model of.</param>
		/// <returns name="model">The pickups model.</returns>
		std::string GetModel(Objects::Entity entity)
		{
			return GetPickupModel(entity);
		}

		/// <summary>
		/// Sets the pickups model
		/// </summary>
		/// <param name="entity">The entity of the pickup you wish to set the model off.</param>
		/// <param name="model">The model/prop name you wish to set the pickup too.</param>
		void SetModel(Objects::Entity entity, const std::string model)
		{
			SetPickupModel(entity, model);
		}

		/// <summary>
		/// Gets the pickups time until it respawns after being pickedup
		/// </summary>
		/// <param name="entity">The entity of the pickup.</param>
		/// <returns name="model">The pickups respawn time.</returns>
		const int GetRespawnDelay(Objects::Entity entity)
		{
			return GetPickupRespawnDelay(entity);
		}

		/// <summary>
		/// Sets the pickups time until it respawns after being pickedup
		/// </summary>
		/// <param name="entity">The entity of the pickup.</param>
		/// <param name="time">The time in MS it takes for the pickup to respawn.</param>
		void SetRespawnDelay(Objects::Entity entity, const int time)
		{
			SetPickupRespawnDelay(entity, time);
		}
	}
}

#endif