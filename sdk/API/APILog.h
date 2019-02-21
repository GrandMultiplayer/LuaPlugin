#ifndef __APILOG_H__
#define __APILOG_H__
#pragma once

namespace API
{
	namespace Log
	{
		DLL_PUBLIC_I_C void Print(const std::string message);
		DLL_PUBLIC_I_C void Debug(const std::string message);
		DLL_PUBLIC_I_C void Warning(const std::string message);
		DLL_PUBLIC_I_C void Error(const std::string message);
	}
}

#endif