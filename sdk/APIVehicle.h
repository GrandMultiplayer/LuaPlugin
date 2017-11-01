#ifndef __APIVEHICLE_H__
#define __APIVEHICLE_H__

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Vehicle
		{
		public:
			/// <summary>
			/// Creates a vehicle of a desired model at the position defined
			/// </summary>
			/// <param name="model">The model of the vehicle you wish to create</param>
			/// <param name="position">The position you wish to create the vehicle at</param>
			/// <param name="heading">The direction you wish the vehicle to be facing</param>
			/// <returns name="entity">The vehicles server entity id</returns>
			DLL_PUBLIC_I static const int Create(const std::string model, const CVector3 position, const float heading);

			/// <summary>
			/// Creates a vehicle of a desired model at the position defined
			/// </summary>
			/// <param name="model">The model of the vehicle you wish to create</param>
			/// <param name="position">The position you wish to create the vehicle at</param>
			/// <param name="heading">The rotation you wish to set the vehicle at</param>
			/// <returns name="entity">The vehicles server entity id</returns>
			DLL_PUBLIC_I static const int Create(const std::string model, const CVector3 position, const CVector3 rotation);

			/// <summary>
			/// Gets the vehicles color using the Games standard preset colors
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="layer">The paint layer to get the color off (1 or 2)</param>
			/// <returns name="color">The standard color being used</returns>
			DLL_PUBLIC_I static const int GetColor(const int entity, const int layer);

			/// <summary>
			/// Gets the vehicles color type. (matt, metalic ect)
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="layer">The paint layer to get the color type off (1 or 2)</param>
			/// <returns name="type">The type of paint being used</returns>
			DLL_PUBLIC_I static const int GetColorType(const int entity, const int layer);

			/// <summary>
			/// Sets the vehicles color using the Games standard preset colors
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="layer">The paint layer to change the color off (1 or 2)</param>
			/// <param name="painttype">The type of paint ( 0: Normal - 1: Metallic - 2 : Pearl - 3 : Matte - 4 : Metal - 5 : Chrome )</param>
			/// <param name="color">The color preset to use</param>
			DLL_PUBLIC_I static void SetColor(const int entity, const int layer, const int painttype, const int color);

			/// <summary>
			/// Gets the vehicles custom color type.
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="layer">The paint layer to get the color off (1 or 2)</param>
			/// <returns name="RGBColor">The type of paint being used</returns>
			DLL_PUBLIC_I static const Color GetCustomColor(const int entity, const int layer);

			/// <summary>
			/// Sets the vehicles color using RGB colors
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="layer">The paint layer to change the color off (1 or 2)</param>
			/// <param name="color">The custom RGB color (alpha is not used)</param>
			DLL_PUBLIC_I static void SetColor(const int entity, const int layer, const Color color);

			/// <summary>
			/// Gets the vehicles number plate
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <returns name="plate">The vehicles number plate</returns>
			DLL_PUBLIC_I static const std::string GetNumberPlate(const int entity);

			/// <summary>
			/// Sets the vehicles number plate
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="plate">The number plate text. (Must be 8 or less chars)</param>
			DLL_PUBLIC_I static void SetNumberPlate(const int entity, const std::string plate);

			/// <summary>
			/// Gets the index of the modType on the vehicle being used
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="modType">The mod type to get the modIndex for (pastebin.com/mL1MUmrf)</param>
			/// <returns name="modIndex">The mod index installed on the vehicle of the mod type</returns>
			DLL_PUBLIC_I static const int GetMod(const int entity, const int modType);

			/// <summary>
			/// Sets the index of the modType on the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="modType">The mod type to set the index of (pastebin.com/mL1MUmrf)</param>
			/// <param name="modIndex">The mod index to use for the modType</param>
			DLL_PUBLIC_I static void SetMod(const int entity, const int modType, const int modIndex);

			/// <summary>
			/// Gets the engine state of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <returns name="state">The engine state</returns>
			DLL_PUBLIC_I static const bool GetEngineState(const int entity);

			/// <summary>
			/// Set the engine state of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="state">The state to set the engine</param>
			/// <param name="instant">Wether to turn the engine on instantly</param>
			DLL_PUBLIC_I static void SetEngineState(const int entity, const bool state, const bool instant);

			/// <summary>
			/// Get the doors locked state of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <returns name="state">The locked state</returns>
			DLL_PUBLIC_I static const int GetDoorsLockState(const int entity);

			/// <summary>
			/// Set the doors locked state of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="state">The state to set the locks (0 - CARLOCK_NONE, 1 - CARLOCK_UNLOCKED, 2 - CARLOCK_LOCKED(locked), 3 - CARLOCK_LOCKOUT_PLAYER_ONLY, 4 - CARLOCK_LOCKED_PLAYER_INSIDE(can get in, can't leave))</param>
			DLL_PUBLIC_I static void SetDoorsLockState(const int entity, const int state);

			/// <summary>
			/// Set the doors locked state of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="state">The state to set the locks (0 - CARLOCK_NONE, 1 - CARLOCK_UNLOCKED, 2 - CARLOCK_LOCKED(locked), 3 - CARLOCK_LOCKOUT_PLAYER_ONLY, 4 - CARLOCK_LOCKED_PLAYER_INSIDE(can get in, can't leave))</param>
			/// <param name="player">The entity of the player you whish to check the vehicles lock state for.</param>
			DLL_PUBLIC_I static void SetDoorsLockState(const int entity, const int state, const int player);

			/// <summary>
			/// Get the vehicles model
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <returns name="model">The model</returns>
			DLL_PUBLIC_I static const std::string GetModel(const int entity);

			/// <summary>
			/// Get the vehicles number plate style
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <returns name="style">The number plate style index</returns>
			DLL_PUBLIC_I static const int GetNumberPlateStyle(const int entity);

			/// <summary>
			/// Set the vehicles number plate style
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="style">The style index of the numberplate</param>
			DLL_PUBLIC_I static void SetNumberPlateStyle(const int entity, const int style);

			/// <summary>
			/// Fetch if a vehicles extra is enabled or not.
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="extra">The extra index (1-14)</param>
			/// <returns name="enabled">The extras toggle state</returns>
			DLL_PUBLIC_I static const bool GetExtra(const int entity, const int extra);

			/// <summary>
			/// Set the vehicles extra toggle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="extra">The style index of the numberplate</param>
			/// <param name="toggle">The toggle state of the extra</param>
			DLL_PUBLIC_I static void SetExtra(const int entity, const int extra, const bool toggle);

			/// <summary>
			/// Gets the vehicle engine health
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <returns name="health">The health of the engine</returns>
			DLL_PUBLIC_I static const float GetEngineHealth(const int entity);

			/// <summary>
			/// Set the vehicles engine health
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="health">The health to set the engine (-4000 - 1000, -4000: Engine is destroyed, 0 and below: Engine catches fire and health rapidly declines, 300 : Engine is smoking and losing functionality, 1000 : Engine is perfect)</param>
			DLL_PUBLIC_I static void SetEngineHealth(const int entity, const float health);

			/// <summary>
			/// Gets the vehicle fuel tank health
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <returns name="health">The health of the fuel tank</returns>
			DLL_PUBLIC_I static const float GetFuelTankHealth(const int entity);

			/// <summary>
			/// Set the vehicles fuel tank health
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="health">The health to set the fuel tank (-999 - 1000)</param>
			DLL_PUBLIC_I static void SetFuelTankHealth(const int entity, const float health);

			/// <summary>
			/// Fixes the vehicles deformation
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			DLL_PUBLIC_I static void FixDeformation(const int entity);

			/// <summary>
			/// Gets the occupant int the seat of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="seat">The seat of the vehicle to get the occupant off (0 = Driver, 1-11 Passenger seats)</param>
			/// <returns name="entity">The entity of the occupant in the seat, -1 if no one</returns>
			DLL_PUBLIC_I static const int GetOccupant(const int entity, const int seat);

			/// <summary>
			/// Gets the occupants of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <returns name="ocupants">The occupants of the vehicle, vector[0] = driver, vector 1-11 = passenger seats</returns>
			DLL_PUBLIC_I static const std::vector<int> GetOccupants(const int entity);

			/// <summary>
			/// Gets the taxi light state of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <returns name="state">The taxi lights state</returns>
			DLL_PUBLIC_I static const bool GetTaxiLightState(const int entity);

			/// <summary>
			/// Sets the taxi light state of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="state">The state to set it</param>
			DLL_PUBLIC_I static void SetTaxiLightState(const int entity, const bool state);

			/// <summary>
			/// Gets the turnlight state of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="turnlight">The turn light state to get, 1 for left light, 0 for right light.</param>
			/// <returns name="state">The turnlight state</returns>
			DLL_PUBLIC_I static const bool GetIndicatorState(const int entity, const int turnlight);

			/// <summary>
			/// Sets the turnlight state of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="turnlight">The turn light state to get, 1 for left light, 0 for right light.</param>
			/// <param name="state">The state to set it</param>
			DLL_PUBLIC_I static void SetIndicatorState(const int entity, const int turnlight, const bool state);

			/// <summary>
			/// Gets the interior light state of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <returns name="state">The interior light state</returns>
			DLL_PUBLIC_I static const bool GetInteriorLightState(const int entity);

			/// <summary>
			/// Sets the interior light state of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="state">The state to set it</param>
			DLL_PUBLIC_I static void SetInteriorLightState(const int entity, const bool state);

			/// <summary>
			/// Gets the sire sound state of the vehicle
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <returns name="state">The siren sound state</returns>
			DLL_PUBLIC_I static const bool GetSirenSoundState(const int entity);

			/// <summary>
			/// Sets the siren sound state of the vehicle, wether the siren plays sound or not.
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <param name="state">The state to set it, true = no siren sound</param>
			DLL_PUBLIC_I static void SetSirenSoundState(const int entity, const bool state);

			/// <summary>
			/// Gets the entity of the vehicle being towed
			/// </summary>
			/// <param name="entity">The entity of the towing vehicle</param>
			/// <returns name="entity">The vehicle entity being towed</returns>
			DLL_PUBLIC_I static const int GetTowedVehicle(const int entity);

			/// <summary>
			/// Sets the vehicle to be towed
			/// </summary>
			/// <param name="towVehicle">The entity of the vehicle that will be towing the other vehicle.</param>
			/// <param name="vehicle">The entity of the vehicle that will be towed.</param>
			DLL_PUBLIC_I static void SetTowedVehicle(const int towVehicle, const int vehicle);

			/// <summary>
			/// Gets wether or not the vehicle is currently being towed.
			/// </summary>
			/// <param name="entity">The entity of the vehicle</param>
			/// <returns name="state">The siren sound state</returns>
			DLL_PUBLIC_I static const bool IsTowed(const int entity);
		};
	}
#ifdef __cplusplus
}
#endif

#endif