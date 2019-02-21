#include "APICheckpoint.h"

namespace API
{
	namespace Checkpoint
	{
		Objects::Entity Create(const CVector3 position, const float radius, const Color color, const int reserved)
		{
			return CreateCheckpoint(position, radius, color, reserved);
		}

		void Show(Objects::Entity checkpointentity, Objects::Entity playerentity)
		{
			ShowCheckpoint(checkpointentity, playerentity);
		}

		void Hide(Objects::Entity checkpointentity, Objects::Entity playerentity)
		{
			HideCheckpoint(checkpointentity, playerentity);
		}

		const int GetType(Objects::Entity checkpointentity)
		{
			return GetCheckpointType(checkpointentity);
		}

		void SetType(Objects::Entity checkpointentity, const int type)
		{
			SetCheckpointType(checkpointentity, type);
		}

		const Color GetColor(Objects::Entity checkpointentity)
		{
			return GetCheckpointColor(checkpointentity);
		}

		void SetColor(Objects::Entity checkpointentity, const Color color)
		{
			SetCheckpointColor(checkpointentity, color);
		}
	}
}