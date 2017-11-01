#ifndef __APIBLIP_H__
#define __APIBLIP_H__

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Blip
		{
		public:
			/// <summary>
			/// Creates a Blip for the entity
			/// </summary>
			/// <param name="entity">The entity you wish to create a blip for.</param>
			DLL_PUBLIC_I static void Create(const int entity);

			/// <summary>
			/// Creates a Blip at a give position
			/// </summary>
			/// <param name="position">The position you wish to create a blip at.</param>
			/// <returns name="entity">The blips server entity id</returns>
			DLL_PUBLIC_I static const int Create(const CVector3 position);

			/// <summary>
			/// Shows the Blip for the Player
			/// </summary>
			/// <param name="entity">The Entity of the blip to show.</param>
			/// <param name="playerEntity">The Entity of the player to show the blip too.</param>
			DLL_PUBLIC_I static void Show(const int entity, const int playerEntity);

			/// <summary>
			/// Hides the Blip for the Player
			/// </summary>
			/// <param name="entity">The Entity of the blip to hide.</param>
			/// <param name="playerEntity">The Entity of the player to hide the blip from.</param>
			DLL_PUBLIC_I static void Hide(const int entity, const int playerEntity);

			/// <summary>
			/// Shows the Blip for all Players
			/// </summary>
			/// <param name="entity">The Entity of the blip to show.</param>
			DLL_PUBLIC_I static void ShowToAll(const int entity);

			/// <summary>
			/// Hides the Blip for all Players
			/// </summary>
			/// <param name="entity">The Entity of the blip to hide.</param>
			DLL_PUBLIC_I static void HideFromAll(const int entity);

			/// <summary>
			/// Gets the Blips color
			/// </summary>
			/// <param name="entity">The Entity of the blip to get the color for.</param>
			/// <returns name="color">The blips color</returns>
			DLL_PUBLIC_I static const int GetColor(const int entity);

			/// <summary>
			/// Sets the blips color
			/// </summary>
			/// <param name="entity">The Entity of the blip to set the color of.</param>
			/// <param name="color">The color to set.</param>
			DLL_PUBLIC_I static void SetColor(const int entity, const int color);

			/// <summary>
			/// Gets the Blips sprite
			/// </summary>
			/// <param name="entity">The Entity of the blip to get the sprite for.</param>
			/// <returns name="sprite">The blips sprite</returns>
			DLL_PUBLIC_I static const int GetSprite(const int entity);

			/// <summary>
			/// Sets the blips sprite
			/// </summary>
			/// <param name="entity">The Entity of the blip to set the sprite of.</param>
			/// <param name="sprite">The sprite to set the blip as.</param>
			DLL_PUBLIC_I static void SetSprite(const int entity, const int sprite);

			/// <summary>
			/// Gets the Blips text
			/// </summary>
			/// <param name="entity">The Entity of the blip to get the text for.</param>
			/// <returns name="text">The blips text</returns>
			DLL_PUBLIC_I static const std::string GetText(const int entity);

			/// <summary>
			/// Sets the blips text
			/// </summary>
			/// <param name="entity">The Entity of the blip to set the text of.</param>
			/// <param name="text">The text to set the blip as.</param>
			DLL_PUBLIC_I static void SetText(const int entity, const std::string text);

			/// <summary>
			/// Gets the Blips short range state
			/// </summary>
			/// <param name="entity">The Entity of the blip to get the short range state for.</param>
			/// <returns name="state">The blips shirt range state</returns>
			DLL_PUBLIC_I static const bool IsShortRanged(const int entity);

			/// <summary>
			/// Sets the blips short range state
			/// </summary>
			/// <param name="entity">The Entity of the blip to set the short range state of.</param>
			/// <param name="state">The state to set the blip short range as.</param>
			DLL_PUBLIC_I static void SetShortRanged(const int entity, const bool state);
		};
	}
#ifdef __cplusplus
}
#endif

#endif