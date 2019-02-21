#ifndef __APIPICKUP_H__
#define __APIPICKUP_H__
#pragma once

#include <string>

#include "../api.h"
#include "../CVector3.h"
#include "../Entity.h"

#ifdef __cplusplus
	DLL_PUBLIC_I_C Objects::Entity CreatePickup(const CVector3 position, std::string model = "prop_beach_volball02");
	DLL_PUBLIC_I_C void ShowPickup(Objects::Entity entity, Objects::Entity playerEntity);
	DLL_PUBLIC_I_C void HidePickup(Objects::Entity entity, Objects::Entity playerEntity);
	DLL_PUBLIC_I_C std::string GetPickupModel(Objects::Entity entity);
	DLL_PUBLIC_I_C void SetPickupModel(Objects::Entity entity, const std::string model);
	DLL_PUBLIC_I_C const int GetPickupRespawnDelay(Objects::Entity entity);
	DLL_PUBLIC_I_C void SetPickupRespawnDelay(Objects::Entity entity, const int time);
#endif

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
#ifdef __cplusplus
		Objects::Entity Create(const CVector3 position, std::string model = "prop_beach_volball02");
#else
		DLL_PUBLIC_I_C Objects::Entity CreatePickup(const CVector3 position, std::string model = "prop_beach_volball02");
#endif

		/// <summary>
		/// Shows the pickup to the desired player.
		/// </summary>
		/// <param name="entity">The entity of the pickup you wish to show.</param>
		/// <param name="playerEntity">The entity of the player you wish to show the pickup too.</param>
#ifdef __cplusplus
		void Show(Objects::Entity entity, Objects::Entity playerEntity);
#else
		DLL_PUBLIC_I_C void ShowPickup(Objects::Entity entity, Objects::Entity playerEntity);
#endif

		/// <summary>
		/// Hides the pickup from the desired player.
		/// </summary>
		/// <param name="entity">The entity of the pickup you wish to hide.</param>
		/// <param name="playerEntity">The entity of the player you wish to hide the pickup from.</param>
#ifdef __cplusplus
		void Hide(Objects::Entity entity, Objects::Entity playerEntity);
#else
		DLL_PUBLIC_I_C void HidePickup(Objects::Entity entity, Objects::Entity playerEntity);
#endif

		/// <summary>
		/// Gets the pickups current model
		/// </summary>
		/// <param name="entity">The entity of the pickup you wish to get the model of.</param>
		/// <returns name="model">The pickups model.</returns>
#ifdef __cplusplus
		std::string GetModel(Objects::Entity entity);
#else
		DLL_PUBLIC_I_C std::string GetPickupModel(Objects::Entity entity);
#endif

		/// <summary>
		/// Sets the pickups model
		/// </summary>
		/// <param name="entity">The entity of the pickup you wish to set the model off.</param>
		/// <param name="model">The model/prop name you wish to set the pickup too.</param>
#ifdef __cplusplus
		void SetModel(Objects::Entity entity, const std::string model);
#else
		DLL_PUBLIC_I_C void SetPickupModel(Objects::Entity entity, const std::string model);
#endif

		/// <summary>
		/// Gets the pickups time until it respawns after being pickedup
		/// </summary>
		/// <param name="entity">The entity of the pickup.</param>
		/// <returns name="model">The pickups respawn time.</returns>
#ifdef __cplusplus
		const int GetRespawnDelay(Objects::Entity entity);
#else
		DLL_PUBLIC_I_C const int GetPickupRespawnDelay(Objects::Entity entity);
#endif

		/// <summary>
		/// Sets the pickups time until it respawns after being pickedup
		/// </summary>
		/// <param name="entity">The entity of the pickup.</param>
		/// <param name="time">The time in MS it takes for the pickup to respawn.</param>
#ifdef __cplusplus
		void SetRespawnDelay(Objects::Entity entity, const int time);
#else
		DLL_PUBLIC_I_C void SetPickupRespawnDelay(Objects::Entity entity, const int time);
#endif
	}
}
#endif