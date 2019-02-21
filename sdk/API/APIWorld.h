#ifndef __APIWORLD_H__
#define __APIWORLD_H__
#pragma once

namespace API
{
	namespace World
	{
		/// <summary>
		/// Gets the World Time
		/// </summary>
		/// <param name="hour">The Hour (this is a pointer)</param>
		/// <param name="minute">The Minute (this is a pointer)</param>
		/// <param name="second">The Second (this is a pointer)</param>
		/// <returns></returns>
		DLL_PUBLIC_I_C void GetTime(int *hour, int *minute, int *second);
		/// <summary>
		/// Sets the World Time
		/// </summary>
		/// <param name="hour">The Hour you wish to set</param>
		/// <param name="minute">The Minute you wish to set</param>
		/// <param name="second">The Second you wish to set</param>
		DLL_PUBLIC_I_C void SetTime(const int hour, const int minute, const int second);
		/// <summary>
		/// Gets the Weather
		/// </summary>
		/// <returns>The current weather on the server</returns>
		DLL_PUBLIC_I_C const std::string GetWeather();
		/// <summary>
		/// Sets the Weather
		/// </summary>
		/// <param name="weather">The weather you wish to set</param>
		DLL_PUBLIC_I_C void SetWeather(const std::string weather);
		/// <summary>
		/// Loads an IPL for all players and future newly connected players
		/// </summary>
		/// <param name="ipl">The name of the IPL</param>
		DLL_PUBLIC_I_C void LoadIPL(const std::string ipl);
		/// <summary>
		/// Loads an IPL for a specific player
		/// </summary>
		/// <param name="ipl">The name of the IPL</param>
		/// <param name="ipl">The entity of the player you wish to load the ipl for</param>
		DLL_PUBLIC_I_C void LoadIPLForPlayer(Objects::Entity entity, const std::string v);
		/// <summary>
		/// Unloads an IPL for all players and future newly connected players
		/// </summary>
		/// <param name="ipl">The name of the IPL</param>
		DLL_PUBLIC_I_C void UnloadIPL(const std::string ipl);
		/// <summary>
		/// Unloads an IPL for a specific player
		/// </summary>
		/// <param name="ipl">The name of the IPL</param>
		/// <param name="ipl">The entity of the player you wish to unload the ipl for</param>
		DLL_PUBLIC_I_C void UnloadIPLForPlayer(Objects::Entity entity, const std::string ipl);
		/// <summary>
		/// Sets the blackout state for everyone
		/// </summary>
		/// <param name="state">The state blackout should be in</param>
		DLL_PUBLIC_I_C void SetBlackout(const bool state);
		/// <summary>
		/// Sets the blackout state for the player
		/// </summary>
		/// <param name="entity">The entity of the player to set the blackout state</param>
		/// <param name="state">The state gblackout should be in</param>
		DLL_PUBLIC_I_C void SetBlackoutForPlayer(Objects::Entity entity, const bool state);
		/// <summary>
		/// Gets the blackout state
		/// </summary>
		/// <returns>The state of the blackout</returns>
		DLL_PUBLIC_I_C const bool IsBlackout();
		/// <summary>
		/// Set whether the ground snow textures should be enabled or not for everyone.
		/// </summary>
		/// <param name="state">The state ground snow textures should be in</param>
		DLL_PUBLIC_I_C void SetGroundSnow(const bool state);
		/// <summary>
		/// Set whether the ground snow textures should be enabled or not for that player entity.
		/// </summary>
		/// <param name="entity">The entity of the player to set the ground snow textures for</param>
		/// <param name="state">The state ground snow textures should be in</param>
		DLL_PUBLIC_I_C void SetGroundSnowForPlayer(Objects::Entity entity, const bool state);
		/// <summary>
		/// Gets wether the ground snow textures state for everyone.
		/// </summary>
		/// <returns>The state of the ground snow textures</returns>
		DLL_PUBLIC_I_C const bool IsGroundSnow();
	}
}
#endif