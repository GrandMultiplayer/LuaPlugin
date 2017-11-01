#ifndef __APIENTITY_H__
#define __APIENTITY_H__

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Entity
		{
		public:
			/// <summary>
			/// Destroys/Removes a entity from the server
			/// </summary>
			/// <param name="entity">The entity you wish to destroy.</param>
			DLL_PUBLIC_I static void Destroy(const int entity);

			/// <summary>
			/// Gets the position of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to get the position of.</param>
			/// <returns name="position">The CVector3 position of the entity</returns>
			DLL_PUBLIC_I static const CVector3 GetPosition(const int entity);

			/// <summary>
			/// Sets the position of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to set the position of.</param>
			/// <param name="position">The position you wish to set the entity at.</param>
			/// <returns></returns>
			DLL_PUBLIC_I static void SetPosition(const int entity, const CVector3 position);

			/// <summary>
			/// Gets the rotation of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to get the rotation of.</param>
			/// <returns name="rotation">The CVector3 rotation of the entity</returns>
			DLL_PUBLIC_I static const CVector3 GetRotation(const int entity);

			/// <summary>
			/// Sets the rotation of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to set the rotation of.</param>
			/// <param name="rotation">The rotation you wish to set they entity at.</param>
			/// <returns></returns>
			DLL_PUBLIC_I static void SetRotation(const int entity, const CVector3 rotation);

			/// <summary>
			/// Gets the Ped Component data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to get their model Components.</param>
			/// <param name="componentid">The componentid of the component you wish to get.</param>
			/// <returns name="PlayerComponents">The PlayerComponents of the desired player/npc and component</returns>
			DLL_PUBLIC_I static const PedComponent GetPedComponent(const int entity, const int componentid);

			/// <summary>
			/// Sets the Ped Component data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to set their model Components.</param>
			/// <param name="componentid">The componentid of the component you wish to set.</param>
			/// <param name="component">The component structure of the component you wish to set.</param>
			DLL_PUBLIC_I static void SetPedComponent(const int entity, const int componentid, const PedComponent component);

			/// <summary>
			/// Gets the head blend data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to get their model headblend data.</param>
			/// <returns name="PlayerHeadBlends">The headblend data of the players model</returns>
			DLL_PUBLIC_I static const PedHeadBlend GetPedHeadBlend(const int entity);

			/// <summary>
			/// Sets the head blend data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to set their model headblend.</param>
			/// <param name="headblend">The headblend data.</param>
			DLL_PUBLIC_I static void SetPedHeadBlend(const int entity, const PedHeadBlend headblend);

			/// <summary>
			/// Gets the headoverlay data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to get their model headoverlay data.</param>
			/// <param name="overlayid">The overlay id you wish to get the data of.</param>
			/// <returns name="headoverlay">The headoverlay data of the overlay id</returns>
			DLL_PUBLIC_I static const PedHeadOverlay GetPedHeadOverlay(const int entity, const int overlayid);

			/// <summary>
			/// Sets the headoverlay data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to set their model headoverlay data.</param>
			/// <param name="overlayid">The overlay id you wish to set the data of.</param>
			/// <param name="overlay">The overlay data.</param>
			DLL_PUBLIC_I static void SetPedHeadOverlay(const int entity, const int overlayid, const PedHeadOverlay overlay);

			/// <summary>
			/// Gets the prop data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to Get their model prop data.</param>
			/// <param name="compotentid">The compotent id you wish to get the data of.</param>
			/// <returns name="prop">The prop data.</returns>
			DLL_PUBLIC_I static const PedProp GetPedProp(const int entity, const int compotentid);

			/// <summary>
			/// Sets the prop data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to set their model prop data.</param>
			/// <param name="compotentid">The compotent id you wish to set the data of.</param>
			/// <param name="compotentid">The prop data.</param>
			DLL_PUBLIC_I static void SetPedProp(const int entity, const int compotentid, const PedProp prop);

			/// <summary>
			/// Gets the face feature data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to get their model face feature data.</param>
			/// <param name="feature">The index you wish to get the data of (Index can be 0 - 19).</param>
			/// <returns name="scale">The face feature scale. (Scale ranges from -1.0 to 1.0)</returns>
			DLL_PUBLIC_I static const float GetPedFaceFeature(const int entity, const int feature);

			/// <summary>
			/// Sets the face feature data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to set their model face feature data.</param>
			/// <param name="feature">The feature you wish to set the data of (Index can be 0 - 19).</param>
			/// <param name="scale">The face feature scale. (Scale ranges from -1.0 to 1.0)</param>
			DLL_PUBLIC_I static void SetPedFaceFeature(const int entity, const int feature, const float scale);

			/// <summary>
			/// Gets the view distance of the entity.
			/// </summary>
			/// <param name="entity">The entity you want to get the view distance of.</param>
			/// <returns name="distacne">The view distance.</returns>
			DLL_PUBLIC_I static const float GetViewDistance(const int entity);

			/// <summary>
			/// Sets the view distance of the entity.
			/// </summary>
			/// <param name="entity">The entity you want to set the view distance of.</param>
			/// <param name="distance">The distance.</param>
			DLL_PUBLIC_I static void SetViewDistance(const int entity, const float distance);

			/// <summary>
			/// Gets a Vector containing the Entity ids of the desired type
			/// </summary>
			/// <param name="type">The type of entity you want the list of.</param>
			/// <returns name="entities">A vector holding the id's of the tpye of entities fetched (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4).</returns>
			DLL_PUBLIC_I static const std::vector<int> GetEntities(const int type);

			/// <summary>
			/// Gets the nametag of the entity
			/// </summary>
			/// <param name="entity">The entity you want to get the nametag of.</param>
			/// <returns name="nametag">The nametag string.</returns>
			DLL_PUBLIC_I static const std::string GetNametag(const int entity);

			/// <summary>
			/// Sets the nametag of the entity
			/// </summary>
			/// <param name="entity">The entity you want to set the nametag of.</param>
			/// <param name="nametag">The text of the nametag.</param>
			DLL_PUBLIC_I static void SetNametag(const int entity, const std::string nametag);

			/// <summary>
			/// Gets the nametag of the entity
			/// </summary>
			/// <param name="entity">The entity you want to get the nametag visibility of.</param>
			/// <returns name="visible">The visiblity state of the nametag.</returns>
			DLL_PUBLIC_I static const bool IsNametagVisible(const int entity);

			/// <summary>
			/// Sets the nametag visibility of the entity
			/// </summary>
			/// <param name="entity">The entity you want to set the nametag visibility of.</param>
			/// <param name="visible">The visibility state to set the nametag.</param>
			DLL_PUBLIC_I static void SetNametagVisible(const int entity, const bool visible);

			/// <summary>
			/// Gets the health bar of the entity
			/// </summary>
			/// <param name="entity">The entity you want to get the health bar visibility of.</param>
			/// <returns name="visible">The visiblity state of the health bar.</returns>
			DLL_PUBLIC_I static const bool IsHealthbarVisible(const int entity);

			/// <summary>
			/// Sets the health bar visibility of the entity
			/// </summary>
			/// <param name="entity">The entity you want to set the health bar visibility of.</param>
			/// <param name="visible">The visibility state to set the health bar.</param>
			DLL_PUBLIC_I static void SetHealthbarVisible(const int entity, const bool visible);

			/// <summary>
			/// Gets the nametag distance to which its display from
			/// </summary>
			/// <param name="entity">The entity you want to get the nametag distance of.</param>
			/// <returns name="distance">The distance of the nametag it displays from.</returns>
			DLL_PUBLIC_I static const float GetNametagDistance(const int entity);

			/// <summary>
			/// Sets the nametag distance to which its display from
			/// </summary>
			/// <param name="entity">The entity you want to set the nametag distance of.</param>
			/// <param name="distance">The distance to display the nametag from.</param>
			DLL_PUBLIC_I static void SetNametagDistance(const int entity, const float distance);

			/// <summary>
			/// Gets the nametag color
			/// </summary>
			/// <param name="entity">The entity you want to get the nametag color of.</param>
			/// <returns name="color">The color of the nametag.</returns>
			DLL_PUBLIC_I static const Color GetNametagColor(const int entity);

			/// <summary>
			/// Sets the nametag color
			/// </summary>
			/// <param name="entity">The entity you want to set the nametag color of.</param>
			/// <param name="color">The color to set the nametag as.</param>
			DLL_PUBLIC_I static void SetNametagColor(const int entity, const Color color);

			/// <summary>
			/// Gets the health of the entity
			/// </summary>
			/// <param name="entity">The entity you want to get the health of.</param>
			/// <returns name="health">The total health the entity has.</returns>
			DLL_PUBLIC_I static const int GetHealth(const int entity);

			/// <summary>
			/// Sets the health of the entity
			/// </summary>
			/// <param name="entity">The entity you want to set the health of.</param>
			/// <param name="health">The amout to set the health too.</param>
			DLL_PUBLIC_I static void SetHealth(const int entity, const int health);

			/// <summary>
			/// Gets the armour of the entity
			/// </summary>
			/// <param name="entity">The entity you want to get the armour of.</param>
			/// <returns name="armour">The total armour the entity has</returns>
			DLL_PUBLIC_I static const int GetArmour(const int entity);

			/// <summary>
			/// Sets the armour of the entity
			/// </summary>
			/// <param name="entity">The entity you want to set the armour of.</param>
			/// <param name="armour">The total to set the armour of the entity too.</param>
			DLL_PUBLIC_I static void SetArmour(const int entity, const int armour);

			/// <summary>
			/// Sets the nametag distance to which its display from
			/// </summary>
			/// <param name="entity">The entity you want to set the nametag distance of.</param>
			/// <returns name="type">(Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)</returns>
			DLL_PUBLIC_I static const int GetType(const int entity);

			/// <summary>
			/// Revives a player or npc from death
			/// </summary>
			/// <param name="entity">The entity of the npc or player you wish to revive.</param>
			DLL_PUBLIC_I static void Revive(const int entity);

			/// <summary>
			/// Returns if the entity is alive
			/// </summary>
			/// <param name="entity">The entity of the npc, player, object or vehicle you wish to check is alive.</param>
			DLL_PUBLIC_I static const bool IsAlive(const int entity);
		};
	}
#ifdef __cplusplus
}
#endif

#endif