#pragma once

#include "Dough/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // Needed for logging some types

namespace Dough
{
	class Log
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

#define DH_ENGINE_TRACE(...)       ::Dough::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define DH_ENGINE_INFO(...)        ::Dough::Log::GetEngineLogger()->info(__VA_ARGS__)
#define DH_ENGINE_WARN(...)        ::Dough::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define DH_ENGINE_ERROR(...)       ::Dough::Log::GetEngineLogger()->error(__VA_ARGS__)
#define DH_ENGINE_CRITICAL(...)    ::Dough::Log::GetEngineLogger()->critical(__VA_ARGS__)
							      
#define DH_TRACE(...)              ::Dough::Log::GetAppLogger()->trace(__VA_ARGS__)
#define DH_INFO(...)               ::Dough::Log::GetAppLogger()->info(__VA_ARGS__)
#define DH_WARN(...)               ::Dough::Log::GetAppLogger()->warn(__VA_ARGS__)
#define DH_ERROR(...)              ::Dough::Log::GetAppLogger()->error(__VA_ARGS__)
#define DH_CRITICAL(...)           ::Dough::Log::GetAppLogger()->critical(__VA_ARGS__)

#define DH_DECLARE_LOGGER(name, macroName)       extern std::shared_ptr<spdlog::logger> s_##name##Logger;\
									             template<typename... Args> FORCEINLINE void macroName##_TRACE(spdlog::format_string_t<Args...> fmt, Args &&... args) { s_##name##Logger->trace(fmt, args...); }\
									             template<typename... Args> FORCEINLINE void macroName##_INFO(spdlog::format_string_t<Args...> fmt, Args &&... args) { s_##name##Logger->info(fmt, args...); }\
									             template<typename... Args> FORCEINLINE void macroName##_WARN(spdlog::format_string_t<Args...> fmt, Args &&... args) { s_##name##Logger->warn(fmt, args...); }\
									             template<typename... Args> FORCEINLINE void macroName##_ERROR(spdlog::format_string_t<Args...> fmt, Args &&... args) { s_##name##Logger->error(fmt, args...); }\
									             template<typename... Args> FORCEINLINE void macroName##_CRITICAL(spdlog::format_string_t<Args...> fmt, Args &&... args) { s_##name##Logger->critical(fmt, args...); }
#define DH_DECLARE_LOGGER_CPP(name, macroName)   std::shared_ptr<spdlog::logger> s_##name##Logger;
#define DH_DEFINE_LOGGER(name)                   if (!s_##name##Logger) { spdlog::set_pattern("%^[%T] %n: %v%$");\
								                 s_##name##Logger = spdlog::stdout_color_mt(#name);\
                                                 s_##name##Logger->set_level(spdlog::level::trace); }

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

#define DH_DECLARE_LOGGER(name, macroName)      template<typename... Args> FORCEINLINE void macroName##_TRACE(spdlog::format_string_t<Args...> fmt, Args &&... args)    { }\
                                            	template<typename... Args> FORCEINLINE void macroName##_INFO(spdlog::format_string_t<Args...> fmt, Args &&... args)     { }\
                                             	template<typename... Args> FORCEINLINE void macroName##_WARN(spdlog::format_string_t<Args...> fmt, Args &&... args)     { }\
                                             	template<typename... Args> FORCEINLINE void macroName##_ERROR(spdlog::format_string_t<Args...> fmt, Args &&... args)    { }\
                                             	template<typename... Args> FORCEINLINE void macroName##_CRITICAL(spdlog::format_string_t<Args...> fmt, Args &&... args) { }
#define DH_DECLARE_LOGGER_CPP(name, macroName)
#define DH_DEFINE_LOGGER(name)

#endif
