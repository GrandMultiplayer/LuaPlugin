#include "APINpc.h"

namespace API
{
	namespace NPC
	{
		Objects::Entity Create(const std::string model, const CVector3 position, const CVector3 rotation)
		{
			return CreateNPC(model, position, rotation);
		}
	}
}