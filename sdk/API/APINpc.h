#ifndef __APINPC_H__
#define __APINPC_H__
#pragma once

#include <string>

#include "../api.h"
#include "../CVector3.h"
#include "../Entity.h"

#ifdef __cplusplus
	DLL_PUBLIC_I_C Objects::Entity CreateNPC(const std::string model, const CVector3 position, const CVector3 rotation);
#endif

namespace API
{
	namespace NPC
	{
		/// <summary>
		/// Creates a NPC of a desired model at the position defined
		/// </summary>
		/// <param name="model">The model of the npc you wish to create</param>
		/// <param name="position">The position you wish to create the npc at</param>
		/// <param name="heading">The heading you wish to have the npc facing</param>
		/// <returns name="entity">The npc server entity id</returns>
#ifdef __cplusplus
		Objects::Entity Create(const std::string model, const CVector3 position, const CVector3 rotation);
#else
		DLL_PUBLIC_I_C Objects::Entity CreateNPC(const std::string model, const CVector3 position, const CVector3 rotation);
#endif
	}
}

#endif