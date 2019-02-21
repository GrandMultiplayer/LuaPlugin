#include "APIBlip.h"

namespace API
{
	namespace Blip
	{
		void Create(Objects::Entity entity)
		{
			CreateBlip(entity);
		}

		Objects::Entity Create(const CVector3 position)
		{
			return CreateBlip_(position);
		}

		void Show(Objects::Entity entity, Objects::Entity playerEntity)
		{
			ShowBlip(entity, playerEntity);
		}

		void Hide(Objects::Entity entity, Objects::Entity playerEntity)
		{
			HideBlip(entity, playerEntity);
		}

		void ShowToAll(Objects::Entity entity)
		{
			ShowBlipToAll(entity);
		}

		void HideFromAll(Objects::Entity entity)
		{
			HideBlipFromAll(entity);
		}

		const int GetColor(Objects::Entity entity)
		{
			return GetBlipColor(entity);
		}

		void SetColor(Objects::Entity entity, const int color)
		{
			SetBlipColor(entity, color);
		}

		const std::string GetText(Objects::Entity entity)
		{
			return GetBlipText(entity);
		}

		void SetText(Objects::Entity entity, const std::string text)
		{
			SetBlipText(entity, text);
		}
	}
}