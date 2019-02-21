#include "APIVehicle.h"

namespace API
{
	namespace Vehicle
	{
		Objects::Entity Create(const char* model, const CVector3 position, const float heading)
		{
			return CreateVehicle(model, position, heading);
		}

		Objects::Entity Create(const char* model, const CVector3 position, const CVector3 rotation)
		{
			return CreateVehicle_(model, position, rotation);
		}
	}
}