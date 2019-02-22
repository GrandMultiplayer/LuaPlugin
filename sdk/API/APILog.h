#ifndef __APILOG_H__
#define __APILOG_H__
#pragma once

namespace API
{
	namespace Log
	{
		DLL_PUBLIC_I_C void Print(const char * message);
		DLL_PUBLIC_I_C void Debug(const char * message);
		DLL_PUBLIC_I_C void Warning(const char * message);
		DLL_PUBLIC_I_C void Error(const char * message);
	}
}

#endif