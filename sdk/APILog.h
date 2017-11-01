#ifndef __APILOG_H__
#define __APILOG_H__

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Log
		{
		public:
			DLL_PUBLIC_I static void Print(const std::string message);
			DLL_PUBLIC_I static void Debug(const std::string message);
			DLL_PUBLIC_I static void Warning(const std::string message);
			DLL_PUBLIC_I static void Error(const std::string message);
		};
	}
#ifdef __cplusplus
}
#endif

#endif