#ifndef __APIBLIP_H__
#define __APIBLIP_H__
#pragma once

#include <string>

#include "../api.h"
#include "../CVector3.h"
#include "../Entity.h"

#ifdef __cplusplus
	DLL_PUBLIC_I_C void CreateBlip(Objects::Entity entity);
	DLL_PUBLIC_I_C Objects::Entity CreateBlip_(const CVector3 position);
	DLL_PUBLIC_I_C void ShowBlip(Objects::Entity entity, Objects::Entity playerEntity);
	DLL_PUBLIC_I_C void HideBlip(Objects::Entity entity, Objects::Entity playerEntity);
	DLL_PUBLIC_I_C void ShowBlipToAll(Objects::Entity entity);
	DLL_PUBLIC_I_C void HideBlipFromAll(Objects::Entity entity);
	DLL_PUBLIC_I_C const int GetBlipColor(Objects::Entity entity);
	DLL_PUBLIC_I_C void SetBlipColor(Objects::Entity entity, const int color);
	DLL_PUBLIC_I_C const std::string GetBlipText(Objects::Entity entity);
	DLL_PUBLIC_I_C void SetBlipText(Objects::Entity entity, const std::string text);
#endif

namespace API
{
	namespace Blip
	{
		/// <summary>
		/// Creates a Blip for the entity
		/// </summary>
		/// <param name="entity">The entity you wish to create a blip for.</param>
#ifdef __cplusplus
		void Create(Objects::Entity entity);
#else
		DLL_PUBLIC_I_C void CreateBlip(Objects::Entity entity);
#endif

		/// <summary>
		/// Creates a Blip at a give position
		/// </summary>
		/// <param name="position">The position you wish to create a blip at.</param>
		/// <returns name="entity">The blips server entity id</returns>
#ifdef __cplusplus
		Objects::Entity Create(const CVector3 position);
#else
		DLL_PUBLIC_I_C Objects::Entity CreateBlip_(const CVector3 position); 
#endif

		/// <summary>
		/// Shows the Blip for the Player
		/// </summary>
		/// <param name="entity">The Entity of the blip to show.</param>
		/// <param name="playerEntity">The Entity of the player to show the blip too.</param>
#ifdef __cplusplus
		void Show(Objects::Entity entity, Objects::Entity playerEntity);
#else
		DLL_PUBLIC_I_C void ShowBlip(Objects::Entity entity, Objects::Entity playerEntity);
#endif

		/// <summary>
		/// Hides the Blip for the Player
		/// </summary>
		/// <param name="entity">The Entity of the blip to hide.</param>
		/// <param name="playerEntity">The Entity of the player to hide the blip from.</param>
#ifdef __cplusplus
		void Hide(Objects::Entity entity, Objects::Entity playerEntity);
#else
		DLL_PUBLIC_I_C void HideBlip(Objects::Entity entity, Objects::Entity playerEntity);
#endif

		/// <summary>
		/// Shows the Blip for all Players
		/// </summary>
		/// <param name="entity">The Entity of the blip to show.</param>
#ifdef __cplusplus
		void ShowToAll(Objects::Entity entity);
#else
		DLL_PUBLIC_I_C void ShowBlipToAll(Objects::Entity entity);
#endif

		/// <summary>
		/// Hides the Blip for all Players
		/// </summary>
		/// <param name="entity">The Entity of the blip to hide.</param>
#ifdef __cplusplus
		void HideFromAll(Objects::Entity entity);
#else
		DLL_PUBLIC_I_C void HideBlipFromAll(Objects::Entity entity);
#endif

		/// <summary>
		/// Gets the Blips color
		/// </summary>
		/// <param name="entity">The Entity of the blip to get the color for.</param>
		/// <returns name="color">The blips color</returns>
#ifdef __cplusplus
		const int GetColor(Objects::Entity entity);
#else
		DLL_PUBLIC_I_C const int GetBlipColor(Objects::Entity entity);
#endif

		/// <summary>
		/// Sets the blips color
		/// </summary>
		/// <param name="entity">The Entity of the blip to set the color of.</param>
		/// <param name="color">The color to set.</param>
#ifdef __cplusplus
		void SetColor(Objects::Entity entity, const int color);
#else
		DLL_PUBLIC_I_C void SetBlipColor(Objects::Entity entity, const int color);
#endif

		/// <summary>
		/// Gets the Blips sprite
		/// </summary>
		/// <param name="entity">The Entity of the blip to get the sprite for.</param>
		/// <returns name="sprite">The blips sprite</returns>
		DLL_PUBLIC_I_C const int GetSprite(Objects::Entity entity);

		/// <summary>
		/// Sets the blips sprite
		/// </summary>
		/// <param name="entity">The Entity of the blip to set the sprite of.</param>
		/// <param name="sprite">The sprite to set the blip as.</param>
		DLL_PUBLIC_I_C void SetSprite(Objects::Entity entity, const int sprite);

		/// <summary>
		/// Gets the Blips text
		/// </summary>
		/// <param name="entity">The Entity of the blip to get the text for.</param>
		/// <returns name="text">The blips text</returns>
#ifdef __cplusplus
		const std::string GetText(Objects::Entity entity);
#else
		DLL_PUBLIC_I_C const std::string GetBlipText(Objects::Entity entity);
#endif

		/// <summary>
		/// Sets the blips text
		/// </summary>
		/// <param name="entity">The Entity of the blip to set the text of.</param>
		/// <param name="text">The text to set the blip as.</param>
#ifdef __cplusplus
		void SetText(Objects::Entity entity, const std::string text);
#else
		DLL_PUBLIC_I_C void SetBlipText(Objects::Entity entity, const std::string text);
#endif

		/// <summary>
		/// Gets the Blips short range state
		/// </summary>
		/// <param name="entity">The Entity of the blip to get the short range state for.</param>
		/// <returns name="state">The blips shirt range state</returns>
		DLL_PUBLIC_I_C const bool IsShortRanged(Objects::Entity entity);

		/// <summary>
		/// Sets the blips short range state
		/// </summary>
		/// <param name="entity">The Entity of the blip to set the short range state of.</param>
		/// <param name="state">The state to set the blip short range as.</param>
		DLL_PUBLIC_I_C void SetShortRanged(Objects::Entity entity, const bool state);
	}
}
#endif