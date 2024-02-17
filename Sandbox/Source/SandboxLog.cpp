#include "SandboxLog.h"

#include <spdlog/sinks/stdout_color_sinks.h>

void Sandbox::DefineLoggers()
{
	DH_DEFINE_LOGGER(Sandbox);
}

DH_DECLARE_LOGGER_CPP(Sandbox, SB);
