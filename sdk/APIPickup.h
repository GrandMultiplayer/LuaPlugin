#ifndef __APIPICKUP_H__
#define __APIPICKUP_H__

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Pickup
		{
		public:
			/// <summary>
			/// Creates a new pickup
			/// </summary>
			/// <param name="position">The position the pickup should be at.</param>
			/// <param name="model">The model you want the pickup to display as.</param>
			/// <returns name="entity">The pickups entity.</returns>
			DLL_PUBLIC_I static const int Create(const CVector3 position, std::string model = "prop_beach_volball02");

			/// <summary>
			/// Shows the pickup to everyone.
			/// </summary>
			/// <param name="entity">The entity of the pickup you wish to show.</param>
			DLL_PUBLIC_I static void ShowToAll(const int entity);

			/// <summary>
			/// Shows the pickup to the desired player.
			/// </summary>
			/// <param name="entity">The entity of the pickup you wish to show.</param>
			/// <param name="playerEntity">The entity of the player you wish to show the pickup too.</param>
			DLL_PUBLIC_I static void Show(const int entity, const int playerEntity);

			/// <summary>
			/// Hides the pickup from everyone.
			/// </summary>
			/// <param name="entity">The entity of the pickup you wish to hide.</param>
			DLL_PUBLIC_I static void HideFromAll(const int entity);

			/// <summary>
			/// Hides the pickup from the desired player.
			/// </summary>
			/// <param name="entity">The entity of the pickup you wish to hide.</param>
			/// <param name="playerEntity">The entity of the player you wish to hide the pickup from.</param>
			DLL_PUBLIC_I static void Hide(const int entity, const int playerEntity);

			/// <summary>
			/// Gets the pickups current model
			/// </summary>
			/// <param name="entity">The entity of the pickup you wish to get the model of.</param>
			/// <returns name="model">The pickups model.</returns>
			DLL_PUBLIC_I static std::string GetModel(const int entity);

			/// <summary>
			/// Sets the pickups model
			/// </summary>
			/// <param name="entity">The entity of the pickup you wish to set the model off.</param>
			/// <param name="model">The model/prop name you wish to set the pickup too.</param>
			DLL_PUBLIC_I static void SetModel(const int entity, const std::string model);

			/// <summary>
			/// Gets the pickups time until it respawns after being pickedup
			/// </summary>
			/// <param name="entity">The entity of the pickup.</param>
			/// <returns name="model">The pickups respawn time.</returns>
			DLL_PUBLIC_I static const int GetRespawnDelay(const int entity);

			/// <summary>
			/// Sets the pickups time until it respawns after being pickedup
			/// </summary>
			/// <param name="entity">The entity of the pickup.</param>
			/// <param name="time">The time in MS it takes for the pickup to respawn.</param>
			DLL_PUBLIC_I static void SetRespawnDelay(const int entity, const int time);
		};
	}
#ifdef __cplusplus
}
#endif

#endif