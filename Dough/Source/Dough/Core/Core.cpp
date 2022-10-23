#include "dhpch.h"
#include "Dough/Core/Core.h"

ppk::assert::implementation::AssertAction::AssertAction AssertHandler(const char* file,
                                                                      int line,
                                                                      const char* function,
                                                                      const char* expression,
                                                                      int level,
                                                                      const char* message)
{
    switch (level)
    {
    case ppk::assert::implementation::AssertLevel::Debug:
        DH_TRACE("Assertion failed! | {0} | Line {1} in file {2}, function {3}.", expression, line, file, function);
        if (message)
            DH_TRACE("With message: {0}", message);
        break;
    case ppk::assert::implementation::AssertLevel::Warning:
        DH_WARN("Assertion failed! | {0} | Line {1} in file {2}, function {3}.", expression, line, file, function);
        if (message)
            DH_WARN("With message: {0}", message);
        break;
    case ppk::assert::implementation::AssertLevel::Error:
        DH_ERROR("Assertion failed! | {0} | Line {1} in file {2}, function {3}.", expression, line, file, function);
        if (message)
            DH_ERROR("With message: {0}", message);
        break;
    case ppk::assert::implementation::AssertLevel::Fatal:
        DH_CRITICAL("Assertion failed! | {0} | Line {1} in file \"{2}\", function \"{3}\".", expression, line, file, function);
        if (message)
            DH_TRACE("With message: {0}", message);
        break;
    default:
        DH_ERROR("Assertion failed with custom level {0}! | {1} | Line {2} in file {3}, function {4}.", level, expression, line, file, function);
        if (message)
            DH_ERROR("With message: {0}", message);
        break;
    }

    return ppk::assert::implementation::AssertAction::Break;
}

namespace Dough
{
    void Init()
    {
        Log::Init();
        ppk::assert::implementation::setAssertHandler(AssertHandler);
    }

}
