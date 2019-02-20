#ifndef __APICHECKPOINT_H__
#define __APICHECKPOINT_H__

DLL_PUBLIC_I_C Objects::Entity CreateCheckpoint(const CVector3 position, const float radius, const Color color, const int reserved);
DLL_PUBLIC_I_C void ShowCheckpoint(Objects::Entity checkpointentity, Objects::Entity playerentity);
DLL_PUBLIC_I_C void HideCheckpoint(Objects::Entity checkpointentity, Objects::Entity playerentity);
DLL_PUBLIC_I_C const int GetCheckpointType(Objects::Entity checkpointentity);
DLL_PUBLIC_I_C void SetCheckpointType(Objects::Entity checkpointentity, const int type);
DLL_PUBLIC_I_C const Color GetCheckpointColor(Objects::Entity checkpointentity);
DLL_PUBLIC_I_C void SetCheckpointColor(Objects::Entity checkpointentity, const Color color);

namespace API
{
	namespace Checkpoint
	{
		/// <summary>
		/// Creates a Checkpoint
		/// </summary>
		/// <param name="position">The you wish the checkpoint to be at.</param>
		/// <param name="radius">The radius of the checkpoint</param>
		/// <param name="color">The color of the checkpoint</param>
		/// <param name="reserved">The reserved type of checkpoint, pastebin.com/raw/iG0NkEhF</param>
		/// <returns name="entity">The checkpoint server entity id</returns>
		Objects::Entity Create(const CVector3 position, const float radius, const Color color, const int reserved)
		{
			return CreateCheckpoint(position, radius, color, reserved);
		}

		/// <summary>
		/// Displays the checkpoint for a player
		/// </summary>
		/// <param name="checkpointentity">The entity of the checkpoint you wish to display.</param>
		/// <param name="playerentity">The entity of the player you wish to display the checkpoint too.  [Tip: -1 will display it too all connected players]</param>
		void Show(Objects::Entity checkpointentity, Objects::Entity playerentity)
		{
			ShowCheckpoint(checkpointentity, playerentity);
		}

		/// <summary>
		/// Hides the checkpoint for a player
		/// </summary>
		/// <param name="checkpointentity">The entity of the checkpoint you wish to hide.</param>
		/// <param name="playerentity">The entity of the player you wish to hide the checkpoint from.  [Tip: -1 will hide it from all connected players]</param>
		void Hide(Objects::Entity checkpointentity, Objects::Entity playerentity)
		{
			HideCheckpoint(checkpointentity, playerentity);
		}

		/// <summary>
		/// Gets the checkpoints near height
		/// </summary>
		/// <param name="checkpointentity">The entity of the checkpoint.</param>
		/// <returns name="height">The checkpoint near height</returns>
		DLL_PUBLIC_I_C const float GetNearHeight(Objects::Entity checkpointentity);

		/// <summary>
		/// Sets the checkpoints near distance height
		/// </summary>
		/// <param name="checkpointentity">The entity of the checkpoint.</param>
		/// <param name="height">The height</param>
		DLL_PUBLIC_I_C void SetNearHeight(Objects::Entity checkpointentity, const float height);

		/// <summary>
		/// Gets the checkpoints far height
		/// </summary>
		/// <param name="checkpointentity">The entity of the checkpoint.</param>
		/// <returns name="height">The checkpoint far height</returns>
		DLL_PUBLIC_I_C const float GetFarHeight(Objects::Entity checkpointentity);

		/// <summary>
		/// Sets the checkpoints far distance height
		/// </summary>
		/// <param name="checkpointentity">The entity of the checkpoint.</param>
		/// <param name="height">The height</param>
		DLL_PUBLIC_I_C void SetFarHeight(Objects::Entity checkpointentity, const float height);

		/// <summary>
		/// Gets the checkpoints graphic pointers position it's pointing too
		/// </summary>
		/// <param name="checkpointentity">The entity of the checkpoint.</param>
		/// <returns name="pointTo">The checkpoints graphic pointers position it's pointing too</returns>
		DLL_PUBLIC_I_C const CVector3 GetPointTo(Objects::Entity checkpointentity);

		/// <summary>
		/// Sets the checkpoints graphic pointer
		/// </summary>
		/// <param name="checkpointentity">The entity of the checkpoint.</param>
		/// <param name="pointTo">The position the checkpoint points too.</param>
		DLL_PUBLIC_I_C void PointTo(Objects::Entity checkpointentity, const CVector3 pointTo);

		/// <summary>
		/// Gets the checkpoints type
		/// </summary>
		/// <param name="checkpointentity">The entity of the checkpoint.</param>
		/// <returns name="type">The checkpoints type</returns>
		const int GetType(Objects::Entity checkpointentity)
		{
			return GetCheckpointType(checkpointentity);
		}

		/// <summary>
		/// Sets the checkpoints type
		/// </summary>
		/// <param name="checkpointentity">The entity of the checkpoint.</param>
		/// <param name="type">The type of checkpoint, pastebin.com/raw/iG0NkEhF</param>
		void SetType(Objects::Entity checkpointentity, const int type)
		{
			SetCheckpointType(checkpointentity, type);
		}

		/// <summary>
		/// Gets the checkpoints color
		/// </summary>
		/// <param name="checkpointentity">The entity of the checkpoint.</param>
		/// <returns name="color">The checkpoints color</returns>
		const Color GetColor(Objects::Entity checkpointentity)
		{
			return GetCheckpointColor(checkpointentity);
		}

		/// <summary>
		/// Sets the checkpoints color
		/// </summary>
		/// <param name="checkpointentity">The entity of the checkpoint.</param>
		/// <param name="color">The color of checkpoint</param>
		void SetColor(Objects::Entity checkpointentity, const Color color)
		{
			SetCheckpointColor(checkpointentity, color);
		}
	}
}

#endif