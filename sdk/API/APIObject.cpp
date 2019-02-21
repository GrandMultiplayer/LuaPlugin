#include "APIObject.h"

namespace API
{
	namespace Object
	{
		Objects::Entity Create(const std::string model, const CVector3 position, const CVector3 rotation, const bool dynamic)
		{
			return CreateObject(model, position, rotation, dynamic);
		}

		Objects::Entity Create(const int hash, const CVector3 position, const CVector3 rotation, const bool dynamic)
		{
			return CreateObject_(hash, position, rotation, dynamic);
		}
	}
}