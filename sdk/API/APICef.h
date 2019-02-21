#ifndef __APICEF_H__
#define __APICEF_H__
#pragma once

namespace API
{
	namespace CEF
	{
		/// <summary>
		/// Sets the browser's URL for the player
		/// </summary>
		/// <param name="entity">The entity you wish to set the URL for</param>
		/// <param name="url">The URL which is supposed to load</param>
		/// <param name="appcode">The JavaScript code that's used to initialize the page's functions</param>
		/// <param name="remote">Whether the loading URL is remote (http/https) or local (from server files)</param>
		DLL_PUBLIC_I_C void LoadURL(Objects::Entity entity, std::string frame, std::string url, std::string appcode = "", bool remote = false);

		/// <summary>
		/// Executes JavaScript for the player
		/// </summary>
		/// <param name="entity">The entity you wish to execute the call for</param>
		/// <param name="call">The JavaScript code you wish to execute</param>
		DLL_PUBLIC_I_C void ExecuteJavaScript(Objects::Entity entity, std::string frame, std::string call);
	}
}

#endif