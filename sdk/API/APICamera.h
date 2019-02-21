#ifndef __APICAMERA_H__
#define __APICAMERA_H__
#pragma once

#include <string>

#include "../api.h"
#include "../CVector3.h"
#include "../Entity.h"

#ifdef __cplusplus
	DLL_PUBLIC_I_C void SetCameraPosition(Objects::Entity entity, const CVector3 position);
	DLL_PUBLIC_I_C void SetCameraRotation(Objects::Entity entity, const CVector3 position);
	DLL_PUBLIC_I_C void ResetCamera(Objects::Entity entity);
	DLL_PUBLIC_I_C void AttachCamera(Objects::Entity player, Objects::Entity entity, const CVector3 offset);
	DLL_PUBLIC_I_C void DetachCamera(Objects::Entity player);
	DLL_PUBLIC_I_C const bool IsCameraActive(Objects::Entity entity);
#endif

namespace API
{
	namespace Camera
	{
		/// <summary>
		/// Sets the players camera position
		/// </summary>
		/// <param name="entity">The player you wish to set the camera position of.</param>
		/// <param name="position">The position to set the camera.</param>
#ifdef __cplusplus
		void SetPosition(Objects::Entity entity, const CVector3 position);
#else
		DLL_PUBLIC_I_C void SetCameraPosition(Objects::Entity entity, const CVector3 position);
#endif

		/// <summary>
		/// Sets the players camera rotation
		/// </summary>
		/// <param name="entity">The player you wish to set the camera rotation of.</param>
		/// <param name="position">The rotation to set the camera.</param>
#ifdef __cplusplus
		void SetRotation(Objects::Entity entity, const CVector3 position);
#else
		DLL_PUBLIC_I_C void SetCameraRotation(Objects::Entity entity, const CVector3 position);
#endif

		/// <summary>
		/// Resets the camera back to the gameplay camera
		/// </summary>
		/// <param name="entity">The player you wish to reset the camera of.</param>
#ifdef __cplusplus
		void Reset(Objects::Entity entity);
#else
		DLL_PUBLIC_I_C void ResetCamera(Objects::Entity entity);
#endif

		/// <summary>
		/// Forces a first person only camera.
		/// </summary>
		/// <param name="entity">The player you wish to force first person on.</param>
		DLL_PUBLIC_I_C void FirstPersonOnly(Objects::Entity entity);

		/// <summary>
		/// Forces a third person only camera.
		/// </summary>
		/// <param name="entity">The player you wish to force third person on.</param>
		DLL_PUBLIC_I_C void ThirdPersonOnly(Objects::Entity entity);

		/// <summary>
		/// Attaches the camera to an entity.
		/// </summary>
		/// <param name="player">The player you wish to attach the camera of.</param>
		/// <param name="entity">The entity you wish to attach the camera to.</param>
		/// <param name="offset">The offset relative from the entity to have the camera attached to.</param>
#ifdef __cplusplus
		void Attach(Objects::Entity player, Objects::Entity entity, const CVector3 offset);
#else
		DLL_PUBLIC_I_C void AttachCamera(Objects::Entity player, Objects::Entity entity, const CVector3 offset);
#endif

		/// <summary>
		/// Detaches the camera from what even entity it may be attached to.
		/// </summary>
		/// <param name="entity">The player you wish to detach the camera of.</param>
#ifdef __cplusplus
		void Detach(Objects::Entity player);
#else
		DLL_PUBLIC_I_C void DetachCamera(Objects::Entity player);
#endif

		/// <summary>
		/// Returns is the players Scripted Camera is active.
		/// </summary>
		/// <param name="entity">The entity of the player.</param>
		/// <returns>The scripted cameras active state</returns>
#ifdef __cplusplus
		const bool IsActive(Objects::Entity entity);
#else
		DLL_PUBLIC_I_C const bool IsCameraActive(Objects::Entity entity);
#endif
	}
}

#endif