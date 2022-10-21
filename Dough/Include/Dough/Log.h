#pragma once

#include "Dough/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // Needed for logging some types

namespace Dough
{
	class DOUGH_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};
}

#ifndef DH_DIST

#define DH_ENGINE_TRACE(...)    ::Dough::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define DH_ENGINE_INFO(...)     ::Dough::Log::GetEngineLogger()->info(__VA_ARGS__)
#define DH_ENGINE_WARN(...)     ::Dough::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define DH_ENGINE_ERROR(...)    ::Dough::Log::GetEngineLogger()->error(__VA_ARGS__)
#define DH_ENGINE_CRITICAL(...) ::Dough::Log::GetEngineLogger()->critical(__VA_ARGS__)

#define DH_TRACE(...)           ::Dough::Log::GetAppLogger()->trace(__VA_ARGS__)
#define DH_INFO(...)            ::Dough::Log::GetAppLogger()->info(__VA_ARGS__)
#define DH_WARN(...)            ::Dough::Log::GetAppLogger()->warn(__VA_ARGS__)
#define DH_ERROR(...)           ::Dough::Log::GetAppLogger()->error(__VA_ARGS__)
#define DH_CRITICAL(...)        ::Dough::Log::GetAppLogger()->critical(__VA_ARGS__)

#else

#define DH_ENGINE_TRACE(...)    
#define DH_ENGINE_INFO(...)     
#define DH_ENGINE_WARN(...)     
#define DH_ENGINE_ERROR(...)    
#define DH_ENGINE_CRITICAL(...) 

#define DH_TRACE(...)           
#define DH_INFO(...)            
#define DH_WARN(...)            
#define DH_ERROR(...)           
#define DH_CRITICAL(...)        

#endif
