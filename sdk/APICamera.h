#ifndef __APICAMERA_H__
#define __APICAMERA_H__

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Camera
		{
		public:
			/// <summary>
			/// Sets the players camera position
			/// </summary>
			/// <param name="entity">The player you wish to set the camera position of.</param>
			/// <param name="position">The position to set the camera.</param>
			DLL_PUBLIC_I static void SetPosition(const int entity, const CVector3 position);

			/// <summary>
			/// Sets the players camera rotation
			/// </summary>
			/// <param name="entity">The player you wish to set the camera rotation of.</param>
			/// <param name="position">The rotation to set the camera.</param>
			DLL_PUBLIC_I static void SetRotation(const int entity, const CVector3 position);

			/// <summary>
			/// Resets the camera back to the gameplay camera
			/// </summary>
			/// <param name="entity">The player you wish to reset the camera of.</param>
			DLL_PUBLIC_I static void Reset(const int entity);

			/// <summary>
			/// Forces a first person only camera.
			/// </summary>
			/// <param name="entity">The player you wish to force first person on.</param>
			DLL_PUBLIC_I static void FirstPersonOnly(const int entity);

			/// <summary>
			/// Forces a third person only camera.
			/// </summary>
			/// <param name="entity">The player you wish to force third person on.</param>
			DLL_PUBLIC_I static void ThirdPersonOnly(const int entity);

			/// <summary>
			/// Attaches the camera to an entity.
			/// </summary>
			/// <param name="player">The player you wish to attach the camera of.</param>
			/// <param name="entity">The entity you wish to attach the camera to.</param>
			/// <param name="offset">The offset relative from the entity to have the camera attached to.</param>
			DLL_PUBLIC_I static void Attach(const int player, const int entity, const CVector3 offset);

			/// <summary>
			/// Detaches the camera from what even entity it may be attached to.
			/// </summary>
			/// <param name="entity">The player you wish to detach the camera of.</param>
			DLL_PUBLIC_I static void Detach(const int player);


		};
	}
#ifdef __cplusplus
}
#endif

#endif