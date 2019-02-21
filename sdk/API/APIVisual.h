#ifndef __APIVISUAL_H__
#define __APIVISUAL_H__
#pragma once

namespace API
{
	namespace Visual
	{
		/// <summary>
		/// Sends a notification message that displays above the game minimap to all clients.
		/// </summary>
		/// <param name="message">The message of the notification</param>
		/// <param name="pic">Picture to display (pastebin.com/XdpJVbHz)</param>
		/// <param name="icontype">The icon type to use (iconTypes: 1 : Chat Box, 2 : Email, 3 : Add Friend Request, 4 : Nothing, 5 : Nothing, 6 : Nothing, 7 : Right Jumping Arrow, 8 : RP Icon, 9 : $ Icon)</param>
		/// <param name="color">The color to display the notification as (gyazo.com/68bd384455fceb0a85a8729e48216e15)</param>
		/// <param name="sender">The sender is the very top header. This can be any string.</param>
		/// <param name="subject">The subject is the header under the sender.</param>
		/// <returns></returns>
		DLL_PUBLIC_I_C void ShowNotification(const std::string message, const std::string pic, const int icontype, const int color, const std::string sender, const std::string subject);

		/// <summary>
		/// Sends a notification message that displays above the game minimap to a specific client.
		/// </summary>
		/// <param name="entity">The entity id of the player you wish to send it too</param>
		/// <param name="message">The message of the notification</param>
		/// <param name="pic">Picture to display (pastebin.com/XdpJVbHz)</param>
		/// <param name="icontype">The icon type to use (iconTypes: 1 : Chat Box, 2 : Email, 3 : Add Friend Request, 4 : Nothing, 5 : Nothing, 6 : Nothing, 7 : Right Jumping Arrow, 8 : RP Icon, 9 : $ Icon)</param>
		/// <param name="color">The color to display the notification as (gyazo.com/68bd384455fceb0a85a8729e48216e15)</param>
		/// <param name="sender">The sender is the very top header. This can be any string.</param>
		/// <param name="subject">The subject is the header under the sender.</param>
		/// <returns></returns>
		DLL_PUBLIC_I_C void ShowNotificationToPlayer(Objects::Entity entity, const std::string message, const std::string pic, const int icontype, const int color, const std::string sender, const std::string subject);

		/// <summary>
		/// Sends a subtitle message that displays on the bottom of the game to all clients
		/// </summary>
		/// <param name="message">The message of the subtitle</param>
		/// <param name="duration">The amount of time the subtitle should be shown (in milliseconds)</param>
		/// <param name="shownow">Whether the subtitle must be showed immediately or not.</param>
		/// <returns></returns>
		DLL_PUBLIC_I_C void ShowSubtitle(const std::string message, const int duration, const bool shownow);

		/// <summary>
		/// Sends a subtitle message that displays on the bottom of the game to a specific client.
		/// </summary>
		/// <param name="entity">The entity id of the player you wish to send it too</param>
		/// <param name="message">The message of the subtitle</param>
		/// <param name="duration">The amount of time the subtitle should be shown (in milliseconds)</param>
		/// <param name="shownow">Whether the subtitle must be showed immediately or not.</param>
		/// <returns></returns>
		DLL_PUBLIC_I_C void ShowSubtitleToPlayer(Objects::Entity entity, const std::string message, const int duration, const bool shownow);

		/// <summary>
		/// Sends a chat message to all clients.
		/// </summary>
		/// <param name="message">The string of the message</param>
		DLL_PUBLIC_I_C void SendChatMessage(const std::string message);

		/// <summary>
		/// Sends a chat message to a client.
		/// </summary>
		/// <param name="entity">The entityid of the player you wish to send the message to.</param>
		/// <param name="message">The string of the message</param>
		DLL_PUBLIC_I_C void SendChatMessageToPlayer(Objects::Entity entity, const std::string message);

		/// <summary>
		/// Enables/disables the cursor on-screen. Works with CEF and ImGui
		/// </summary>
		/// <param name="entity">The entityid of the player you wish to enable/disable the cursor of.</param>
		/// <param name="show">Whether to show the cursor or not (true/false)</param>
		DLL_PUBLIC_I_C void ShowCursor(Objects::Entity entity, bool show);

		/// <summary>
		/// Gets display the state of the players GTAV hud
		/// </summary>
		/// <param name="entity">The entity of the player you wish to get the state of their GATV hud.</param>
		/// <returns name="state">The state the display of the hud is in.</returns>
		DLL_PUBLIC_I_C const bool IsHudHidden(Objects::Entity entity);

		/// <summary>
		/// Enables/disables the GTAV hud for the player
		/// </summary>
		/// <param name="entity">The entity of the player you wish to enable/disable the game hud of.</param>
		/// <param name="show">Whether to show the GTAV hud or not (true/false)</param>
		DLL_PUBLIC_I_C void DisplayHud(Objects::Entity entity, bool show);

		/// <summary>
		/// Gets the display state of the players minimap
		/// </summary>
		/// <param name="entity">The entity of the player you wish to get the state of their GATV minimap.</param>
		/// <returns name="state">The state the display of the minimap is in.</returns>
		DLL_PUBLIC_I_C const bool IsRadarHidden(Objects::Entity entity);

		/// <summary>
		/// Enables/disables the GTAV minimap/radar for the player
		/// </summary>
		/// <param name="entity">The entity of the player you wish to enable/disable the minimap of.</param>
		/// <param name="show">Whether to show the GTAV minimap or not (true/false)</param>
		DLL_PUBLIC_I_C void DisplayRadar(Objects::Entity entity, bool show);

		/// <summary>
		/// Gets the display state of the players cash
		/// </summary>
		/// <param name="entity">The entity of the player you wish to get the state of their GATV cash.</param>
		/// <returns name="state">The state the display of the cash is in.</returns>
		DLL_PUBLIC_I_C const bool IsCashHidden(Objects::Entity entity);

		/// <summary>
		/// Enables/disables the GTAV cash hud for the player
		/// </summary>
		/// <param name="entity">The entity of the player you wish to enable/disable the cash of.</param>
		/// <param name="show">Whether to show the GTAV cash or not (true/false)</param>
		DLL_PUBLIC_I_C void DisplayCash(Objects::Entity entity, bool show);

		/// <summary>
		/// Gets the display state of the players ammo gui element (true being the default game state of display ammo, false never display)
		/// </summary>
		/// <param name="entity">The entity of the player you wish to get the state of their GATV ammo gui element.</param>
		/// <returns name="state">The state the display of the ammo gui element is in.</returns>
		DLL_PUBLIC_I_C const bool IsAmmoHidden(Objects::Entity entity);

		/// <summary>
		/// Enables/disables the GTAV ammo gui element for the player
		/// </summary>
		/// <param name="entity">The entity of the player you wish to enable/disable the ammo gui element of.</param>
		/// <param name="show">Whether to show the GTAV ammo gui element or not (true/false)</param>
		DLL_PUBLIC_I_C void DisplayAmmo(Objects::Entity entity, bool show);
	}
}

#endif