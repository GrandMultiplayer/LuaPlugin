#ifndef __APIENTITY_H__
#define __APIENTITY_H__
#pragma once

namespace API
{
	namespace Entity
	{
		/// <summary>
		/// Destroys/Removes a entity from the server
		/// </summary>
		/// <param name="entity">The entity you wish to destroy.</param>
		DLL_PUBLIC_I_C void Destroy(Objects::Entity entity);

		/// <summary>
		/// Gets the position of the entity.
		/// </summary>
		/// <param name="entity">The entity you wish to get the position of.</param>
		/// <returns name="position">The CVector3 position of the entity</returns>
		DLL_PUBLIC_I_C const CVector3 GetPosition(Objects::Entity entity);

		/// <summary>
		/// Sets the position of the entity.
		/// </summary>
		/// <param name="entity">The entity you wish to set the position of.</param>
		/// <param name="position">The position you wish to set the entity at.</param>
		/// <returns></returns>
		DLL_PUBLIC_I_C void SetPosition(Objects::Entity entity, const CVector3 position);

		/// <summary>
		/// Gets the rotation of the entity.
		/// </summary>
		/// <param name="entity">The entity you wish to get the rotation of.</param>
		/// <returns name="rotation">The CVector3 rotation of the entity</returns>
		DLL_PUBLIC_I_C const CVector3 GetRotation(Objects::Entity entity);

		/// <summary>
		/// Sets the rotation of the entity.
		/// </summary>
		/// <param name="entity">The entity you wish to set the rotation of.</param>
		/// <param name="rotation">The rotation you wish to set they entity at.</param>
		/// <returns></returns>
		DLL_PUBLIC_I_C void SetRotation(Objects::Entity entity, const CVector3 rotation);

		/// <summary>
		/// Gets the Ped Component data of the player or npc entity.
		/// </summary>
		/// <param name="entity">The entity of the player or npc you wish to get their model Components.</param>
		/// <param name="componentid">The componentid of the component you wish to get.</param>
		/// <returns name="PlayerComponents">The PlayerComponents of the desired player/npc and component</returns>
		DLL_PUBLIC_I_C const GrandM::Model::Component GetPedComponent(Objects::Entity entity, const int componentid);

		/// <summary>
		/// Sets the Ped Component data of the player or npc entity.
		/// </summary>
		/// <param name="entity">The entity of the player or npc you wish to set their model Components.</param>
		/// <param name="componentid">The componentid of the component you wish to set.</param>
		/// <param name="component">The component structure of the component you wish to set.</param>
		DLL_PUBLIC_I_C void SetPedComponent(Objects::Entity entity, const int componentid, const GrandM::Model::Component component);

		/// <summary>
		/// Gets the head blend data of the player or npc entity.
		/// </summary>
		/// <param name="entity">The entity of the player or npc you wish to get their model headblend data.</param>
		/// <returns name="PlayerHeadBlends">The headblend data of the players model</returns>
		DLL_PUBLIC_I_C const GrandM::Model::HeadBlend GetPedHeadBlend(Objects::Entity entity);

		/// <summary>
		/// Sets the head blend data of the player or npc entity.
		/// </summary>
		/// <param name="entity">The entity of the player or npc you wish to set their model headblend.</param>
		/// <param name="headblend">The headblend data.</param>
		DLL_PUBLIC_I_C void SetPedHeadBlend(Objects::Entity entity, const GrandM::Model::HeadBlend headblend);

		/// <summary>
		/// Gets the headoverlay data of the player or npc entity.
		/// </summary>
		/// <param name="entity">The entity of the player or npc you wish to get their model headoverlay data.</param>
		/// <param name="overlayid">The overlay id you wish to get the data of.</param>
		/// <returns name="headoverlay">The headoverlay data of the overlay id</returns>
		DLL_PUBLIC_I_C const GrandM::Model::HeadOverlay GetPedHeadOverlay(Objects::Entity entity, const int overlayid);

		/// <summary>
		/// Sets the headoverlay data of the player or npc entity.
		/// </summary>
		/// <param name="entity">The entity of the player or npc you wish to set their model headoverlay data.</param>
		/// <param name="overlayid">The overlay id you wish to set the data of.</param>
		/// <param name="overlay">The overlay data.</param>
		DLL_PUBLIC_I_C void SetPedHeadOverlay(Objects::Entity entity, const int overlayid, const GrandM::Model::HeadOverlay overlay);

		/// <summary>
		/// Gets the prop data of the player or npc entity.
		/// </summary>
		/// <param name="entity">The entity of the player or npc you wish to Get their model prop data.</param>
		/// <param name="compotentid">The compotent id you wish to get the data of.</param>
		/// <returns name="prop">The prop data.</returns>
		DLL_PUBLIC_I_C const GrandM::Model::Prop GetPedProp(Objects::Entity entity, const int compotentid);

		/// <summary>
		/// Sets the prop data of the player or npc entity.
		/// </summary>
		/// <param name="entity">The entity of the player or npc you wish to set their model prop data.</param>
		/// <param name="compotentid">The compotent id you wish to set the data of.</param>
		/// <param name="compotentid">The prop data.</param>
		DLL_PUBLIC_I_C void SetPedProp(Objects::Entity entity, const int compotentid, const GrandM::Model::Prop prop);

		/// <summary>
		/// Gets the face feature data of the player or npc entity.
		/// </summary>
		/// <param name="entity">The entity of the player or npc you wish to get their model face feature data.</param>
		/// <param name="feature">The index you wish to get the data of (Index can be 0 - 19).</param>
		/// <returns name="scale">The face feature scale. (Scale ranges from -1.0 to 1.0)</returns>
		DLL_PUBLIC_I_C const float GetPedFaceFeature(Objects::Entity entity, const int feature);

		/// <summary>
		/// Sets the face feature data of the player or npc entity.
		/// </summary>
		/// <param name="entity">The entity of the player or npc you wish to set their model face feature data.</param>
		/// <param name="feature">The feature you wish to set the data of (Index can be 0 - 19).</param>
		/// <param name="scale">The face feature scale. (Scale ranges from -1.0 to 1.0)</param>
		DLL_PUBLIC_I_C void SetPedFaceFeature(Objects::Entity entity, const int feature, const float scale);

		/// <summary>
		/// Gets the view distance of the entity.
		/// </summary>
		/// <param name="entity">The entity you want to get the view distance of.</param>
		/// <returns name="distacne">The view distance.</returns>
		DLL_PUBLIC_I_C const float GetViewDistance(Objects::Entity entity);

		/// <summary>
		/// Sets the view distance of the entity.
		/// </summary>
		/// <param name="entity">The entity you want to set the view distance of.</param>
		/// <param name="distance">The distance.</param>
		DLL_PUBLIC_I_C void SetViewDistance(Objects::Entity entity, const float distance);

		/// <summary>
		/// Gets a Vector containing the Entity ids of the desired type
		/// </summary>
		/// <param name="type">The type of entity you want the list of.</param>
		/// <returns name="entities">A vector holding the id's of the tpye of entities fetched (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4).</returns>
		DLL_PUBLIC_I_C Objects::Entity * GetEntities(const int type);

		/// <summary>
		/// Gets the nametag of the entity
		/// </summary>
		/// <param name="entity">The entity you want to get the nametag of.</param>
		/// <returns name="nametag">The nametag string.</returns>
		DLL_PUBLIC_I_C const std::string GetNametag(Objects::Entity entity);

		/// <summary>
		/// Sets the nametag of the entity
		/// </summary>
		/// <param name="entity">The entity you want to set the nametag of.</param>
		/// <param name="nametag">The text of the nametag.</param>
		DLL_PUBLIC_I_C void SetNametag(Objects::Entity entity, const std::string nametag);

		/// <summary>
		/// Gets the nametag of the entity
		/// </summary>
		/// <param name="entity">The entity you want to get the nametag visibility of.</param>
		/// <returns name="visible">The visiblity state of the nametag.</returns>
		DLL_PUBLIC_I_C const bool IsNametagVisible(Objects::Entity entity);

		/// <summary>
		/// Sets the nametag visibility of the entity
		/// </summary>
		/// <param name="entity">The entity you want to set the nametag visibility of.</param>
		/// <param name="visible">The visibility state to set the nametag.</param>
		DLL_PUBLIC_I_C void SetNametagVisible(Objects::Entity entity, const bool visible);

		/// <summary>
		/// Gets the health bar of the entity
		/// </summary>
		/// <param name="entity">The entity you want to get the health bar visibility of.</param>
		/// <returns name="visible">The visiblity state of the health bar.</returns>
		DLL_PUBLIC_I_C const bool IsHealthbarVisible(Objects::Entity entity);

		/// <summary>
		/// Sets the health bar visibility of the entity
		/// </summary>
		/// <param name="entity">The entity you want to set the health bar visibility of.</param>
		/// <param name="visible">The visibility state to set the health bar.</param>
		DLL_PUBLIC_I_C void SetHealthbarVisible(Objects::Entity entity, const bool visible);

		/// <summary>
		/// Gets the nametag distance to which its display from
		/// </summary>
		/// <param name="entity">The entity you want to get the nametag distance of.</param>
		/// <returns name="distance">The distance of the nametag it displays from.</returns>
		DLL_PUBLIC_I_C const float GetNametagDistance(Objects::Entity entity);

		/// <summary>
		/// Sets the nametag distance to which its display from
		/// </summary>
		/// <param name="entity">The entity you want to set the nametag distance of.</param>
		/// <param name="distance">The distance to display the nametag from.</param>
		DLL_PUBLIC_I_C void SetNametagDistance(Objects::Entity entity, const float distance);

		/// <summary>
		/// Gets the nametag color
		/// </summary>
		/// <param name="entity">The entity you want to get the nametag color of.</param>
		/// <returns name="color">The color of the nametag.</returns>
		DLL_PUBLIC_I_C const Color GetNametagColor(Objects::Entity entity);

		/// <summary>
		/// Sets the nametag color
		/// </summary>
		/// <param name="entity">The entity you want to set the nametag color of.</param>
		/// <param name="color">The color to set the nametag as.</param>
		DLL_PUBLIC_I_C void SetNametagColor(Objects::Entity entity, const Color color);

		/// <summary>
		/// Gets the health of the entity
		/// </summary>
		/// <param name="entity">The entity you want to get the health of.</param>
		/// <returns name="health">The total health the entity has.</returns>
		DLL_PUBLIC_I_C const int GetHealth(Objects::Entity entity);

		/// <summary>
		/// Sets the health of the entity
		/// </summary>
		/// <param name="entity">The entity you want to set the health of.</param>
		/// <param name="health">The amout to set the health too.</param>
		DLL_PUBLIC_I_C void SetHealth(Objects::Entity entity, const int health);

		/// <summary>
		/// Gets the armour of the entity
		/// </summary>
		/// <param name="entity">The entity you want to get the armour of.</param>
		/// <returns name="armour">The total armour the entity has</returns>
		DLL_PUBLIC_I_C const int GetArmour(Objects::Entity entity);

		/// <summary>
		/// Sets the armour of the entity
		/// </summary>
		/// <param name="entity">The entity you want to set the armour of.</param>
		/// <param name="armour">The total to set the armour of the entity too.</param>
		DLL_PUBLIC_I_C void SetArmour(Objects::Entity entity, const int armour);

		/// <summary>
		/// Revives a player or npc from death
		/// </summary>
		/// <param name="entity">The entity of the npc or player you wish to revive.</param>
		DLL_PUBLIC_I_C void Revive(Objects::Entity entity);

		/// <summary>
		/// Returns if the entity is alive
		/// </summary>
		/// <param name="entity">The entity of the npc, player, object or vehicle you wish to check is alive.</param>
		DLL_PUBLIC_I_C const bool IsAlive(Objects::Entity entity);
	}
}

#endif