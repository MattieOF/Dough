#pragma once

#ifdef DH_PLATFORM_WINDOWS
	#ifdef DH_BUILD_DLL
		#define DOUGH_API __declspec(dllexport)
	#else
		#define DOUGH_API __declspec(dllimport)
	#endif
#else
	#error Dough currently only supports Windows.
#endif
