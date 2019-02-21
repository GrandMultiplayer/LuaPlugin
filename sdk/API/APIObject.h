#ifndef __APIOBJECT_H__
#define __APIOBJECT_H__
#pragma once

#include <string>

#include "../api.h"
#include "../CVector3.h"
#include "../Entity.h"

#ifdef __cplusplus
	DLL_PUBLIC_I_C Objects::Entity CreateObject(const std::string model, const CVector3 position, const CVector3 rotation, const bool dynamic);
	DLL_PUBLIC_I_C Objects::Entity CreateObject_(const int hash, const CVector3 position, const CVector3 rotation, const bool dynamic);
#endif

namespace API
{
	namespace Object
	{
		/// <summary>
		/// Creates a object of a desired model at the position defined
		/// </summary>
		/// <param name="model">The model of the object you wish to create</param>
		/// <param name="position">The position you wish to create the object at</param>
		/// <param name="rotation">The rotation you wish to create the object with</param>
		/// <param name="dynamic">If the object should be dynamic or not. (has physics or not)</param>
		/// <returns name="entity">The objects server entity id</returns>
#ifdef __cplusplus
		Objects::Entity Create(const std::string model, const CVector3 position, const CVector3 rotation, const bool dynamic);
#else
		DLL_PUBLIC_I_C Objects::Entity CreateObject(const std::string model, const CVector3 position, const CVector3 rotation, const bool dynamic);
#endif

		/// <summary>
		/// Creates a object of a desired hash of a model name at the position defined
		/// </summary>
		/// <param name="hash">The hash of the model name of the object you wish to create</param>
		/// <param name="position">The position you wish to create the object at</param>
		/// <param name="rotation">The rotation you wish to create the object with</param>
		/// <param name="dynamic">If the object should be dynamic or not. (has physics or not)</param>
		/// <returns name="entity">The objects server entity id</returns>
#ifdef __cplusplus
		Objects::Entity Create(const int hash, const CVector3 position, const CVector3 rotation, const bool dynamic);
#else
		DLL_PUBLIC_I_C Objects::Entity CreateObject_(const int hash, const CVector3 position, const CVector3 rotation, const bool dynamic);
#endif

		/// <summary>
		/// Gets the texture variation of the object entity.
		/// </summary>
		/// <param name="entity">The enity of the objetc you wish to get the texture variation of</param>
		DLL_PUBLIC_I_C const int GetTextureVariation(Objects::Entity entity);

		/// <summary>
		/// Sets the texture variation of the object entity.
		/// </summary>
		/// <param name="entity">The enity of the objetc you wish to set the texture variation of</param>
		/// <param name="textureindex">The texture id/index</param>
		DLL_PUBLIC_I_C void SetTextureVariation(Objects::Entity entity, const int textureindex);
	}
}

#endif