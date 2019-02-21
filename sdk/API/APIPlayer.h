#ifndef __APIPLAYER_H__
#define __APIPLAYER_H__
#pragma once

namespace API
{
	namespace Player
	{
		/// <summary>
		/// Gets the model of the player entity.
		/// </summary>
		/// <param name="entity">The entity of the player you wish to get the model of.</param>
		/// <returns name="model">The player model the player currently has.</returns>
		DLL_PUBLIC_I_C const std::string GetPlayerModel(Objects::Entity entity);

		/// <summary>
		/// Sets the model of the player entity.
		/// </summary>
		/// <param name="entity">The entity of the player you wish to set the model of.</param>
		/// <param name="model">The model you wish to set on the player.</param>
		DLL_PUBLIC_I_C void SetPlayerModel(Objects::Entity entity, const std::string model);

		/// <summary>
		/// Gets the username of the player entity.
		/// </summary>
		/// <param name="entity">The entity of the player to get the username of.</param>
		/// <returns name="name">The players username.</returns>
		DLL_PUBLIC_I_C const std::string GetUsername(Objects::Entity entity);

		/// <summary>
		/// Sets the username of the player entity.
		/// </summary>
		/// <param name="entity">The entity of the player to get the username of.</param>
		/// <param name="name">What to set their username as.</param>
		DLL_PUBLIC_I_C void SetUsername(Objects::Entity entity, const std::string name);

		/// <summary>
		/// Gets the players controls state.
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <returns name="disabled">The disabled controls state.</returns>
		DLL_PUBLIC_I_C const bool IsControllable(Objects::Entity entity);

		/// <summary>
		/// Set the players controls state.
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <param name="disablecontrols">The state to set the controls disabled state in.</param>
		/// <param name="frozen">Wether the player should be frozen in place.</param>
		DLL_PUBLIC_I_C void SetControllable(Objects::Entity entity, bool disablecontrols, bool frozen = false);

		/// <summary>
		/// Gets the players ip
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <returns name="ip">The ip of the user in string form.</returns>
		DLL_PUBLIC_I_C const std::string GetIP(Objects::Entity entity);

		/// <summary>
		/// Gets the players secret key that identifies them
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <returns name="ip">The secret key of the user, this is uniqe to them.</returns>
		DLL_PUBLIC_I_C const std::string GetSecretKey(Objects::Entity entity);

		/// <summary>
		/// Kicks the player with reason
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <param name="reason">The reason for kicking the player.</param>
		DLL_PUBLIC_I_C void Kick(Objects::Entity entity, const std::string reason);

		/// <summary>
		/// Put the player in the desired vehicle and seat
		/// </summary>
		/// <param name="playerEntity">The entity of the player.</param>
		/// <param name="vehicleEntity">The entity of the vehicle.</param>
		/// <param name="seat">The seat 0 = driver, 1+ passegners.</param>
		DLL_PUBLIC_I_C void PutInVehicle(Objects::Entity playerEntity, Objects::Entity vehicleEntity, const int seat);

		/// <summary>
		/// Get the vehicle entity the player is in
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <returns name="entity">The entity of the vehicle the player is in, -1 for not in one.</returns>
		DLL_PUBLIC_I_C Objects::Entity GetVehicle(Objects::Entity entity);

		/// <summary>
		/// Get the seat the player is in
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <returns name="seat">The seat the player is in, -1 if none</returns>
		DLL_PUBLIC_I_C const int GetSeat(Objects::Entity entity);

		/// <summary>
		/// Gives the player a Weapon
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <param name="weapon">The weapon to give.</param>
		/// <param name="entity">The ammount of ammo to give.</param>
		DLL_PUBLIC_I_C void GiveWeapon(Objects::Entity entity, const std::string weapon, const int ammo = 0);

		/// <summary>
		/// Removes the weapon from a player
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <param name="weapon">The weapon to remove.</param>
		DLL_PUBLIC_I_C void RemoveWeapon(Objects::Entity entity, const std::string weapon);

		/// <summary>
		/// Gets the weapons ammo and clip ammo
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <param name="weapon">The weapon to get the ammo off.</param>
		/// <param name="ammo">The ammo the player has.</param>
		/// <param name="clipAmmo">The ammo count in the clip.</param>
		DLL_PUBLIC_I_C void GetWeaponAmmo(Objects::Entity entity, const std::string weapon, int* ammo, int* clipAmmo);

		/// <summary>
		/// Sets the weapons ammo and clip ammo
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <param name="weapon">The weapon to set the ammo off.</param>
		/// <param name="ammo">The ammo the player has.</param>
		/// <param name="clipAmmo">The ammo count in the clip.</param>
		DLL_PUBLIC_I_C void SetWeaponAmmo(Objects::Entity entity, const std::string weapon, const int ammo, const int clipAmmo);

		/// <summary>
		/// Gets the players current weapons
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		DLL_PUBLIC_I_C std::string * GetWeapons(Objects::Entity entity);

		/// <summary>
		/// Equoips the weapons for the player
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <param name="weapon">The weapon to equip.</param>
		DLL_PUBLIC_I_C void EquipWeapon(Objects::Entity entity, const std::string weapon);
	};
}

#endif