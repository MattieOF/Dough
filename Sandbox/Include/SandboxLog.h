#pragma once

#include "Dough/Core/Log.h"

DH_DECLARE_LOGGER(Sandbox);

#ifndef DH_DIST
	#define SANDBOX_TRACE(...)     s_SandboxLogger->trace(__VA_ARGS__)
	#define SANDBOX_INFO(...)      s_SandboxLogger->info(__VA_ARGS__)
	#define SANDBOX_WARN(...)      s_SandboxLogger->warn(__VA_ARGS__)
	#define SANDBOX_ERROR(...)     s_SandboxLogger->error(__VA_ARGS__)
	#define SANDBOX_CRITICAL(...)  s_SandboxLogger->critical(__VA_ARGS__)
#else
	#define SANDBOX_TRACE(...)   
	#define SANDBOX_INFO(...)    
	#define SANDBOX_WARN(...)    
	#define SANDBOX_ERROR(...)   
	#define SANDBOX_CRITICAL(...)
#endif
