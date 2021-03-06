#ifndef ZE_DEFINES_HPP
#define ZE_DEFINES_HPP

#include "zeconfig.hpp"
#include "zucchini/platform.hpp"
#include "zucchini/types.hpp"

#include <cstring>

#define FLAG(shift) (1 << shift)
#define MACRO_TO_STRING(x) TO_STRING(x)
#define TO_STRING(str) #str

#ifdef ZE_PLATFORM_WINDOWS
   #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
   #define __FILENAME__ (strrchr(__FILE__, '/' ) ? strrchr(__FILE__, '/' ) + 1 : __FILE__)
#endif

#define CURRENT_SOURCE_LOCATION SourceLocation{__FILENAME__, static_cast<unsigned int>(__LINE__), __func__ }

/*
#define ZE_INFO_OUTPUT     ::ze::Core::UseCoreLogger().info()
#define ZE_DEBUG_OUTPUT    ::ze::Core::UseCoreLogger().debug()
#define ZE_WARN_OUTPUT     ::ze::Core::UseCoreLogger().warn()
#define ZE_ERROR_OUTPUT    ::ze::Core::UseCoreLogger().error()
#define ZE_CRITICAL_OUTPUT ::ze::Core::UseCoreLogger().critical()

#define ZE_LOG_INFO(...)     ::ze::Core::UseCoreLogger().info().logLine(__VA_ARGS__)
#define ZE_LOG_DEBUG(...)    ::ze::Core::UseCoreLogger().debug().logLine(__VA_ARGS__)
#define ZE_LOG_WARN(...)     ::ze::Core::UseCoreLogger().warn().logLine(__VA_ARGS__)
#define ZE_LOG_ERROR(...)    ::ze::Core::UseCoreLogger().error().logLine(__VA_ARGS__)
#define ZE_LOG_CRITICAL(...) ::ze::Core::UseCoreLogger().critical().logLine(__VA_ARGS__)

#define APP_INFO_OUTPUT     ::ze::Core::UseAppLogger().info()
#define APP_DEBUG_OUTPUT    ::ze::Core::UseAppLogger().debug()
#define APP_WARN_OUTPUT     ::ze::Core::UseAppLogger().warn()
#define APP_ERROR_OUTPUT    ::ze::Core::UseAppLogger().error()
#define APP_CRITICAL_OUTPUT ::ze::Core::UseAppLogger().critical()

#define APP_LOG_INFO(...)     ::ze::Core::UseAppLogger().info().logLine(__VA_ARGS__)
#define APP_LOG_DEBUG(...)    ::ze::Core::UseAppLogger().debug().logLine(__VA_ARGS__)
#define APP_LOG_WARN(...)     ::ze::Core::UseAppLogger().warn().logLine(__VA_ARGS__)
#define APP_LOG_ERROR(...)    ::ze::Core::UseAppLogger().error().logLine(__VA_ARGS__)
#define APP_LOG_CRITICAL(...) ::ze::Core::UseAppLogger().critical().logLine(__VA_ARGS__)
*/

#endif // ZE_DEFINES_HPP

