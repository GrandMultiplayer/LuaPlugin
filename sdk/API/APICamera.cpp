#include "APICamera.h"

namespace API
{
	namespace Camera
	{
		void SetPosition(Objects::Entity entity, const CVector3 position)
		{
			SetCameraPosition(entity, position);
		}

		void SetRotation(Objects::Entity entity, const CVector3 position)
		{
			SetCameraRotation(entity, position);
		}

		void Reset(Objects::Entity entity)
		{
			ResetCamera(entity);
		}

		void Attach(Objects::Entity player, Objects::Entity entity, const CVector3 offset)
		{
			AttachCamera(player, entity, offset);
		}

		void Detach(Objects::Entity player)
		{
			DetachCamera(player);
		}

		const bool IsActive(Objects::Entity entity)
		{
			return IsCameraActive(entity);
		}
	}
}