#ifndef ZG_DEFINES_HPP
#define ZG_DEFINES_HPP

#include <zucchini/defines.hpp>
#include "zgconfig.hpp"
#include "platform.hpp"

#define GFX_INFO_OUTPUT     ::zg::GraphicsEngine::UseGraphicsLogger().info()
#define GFX_DEBUG_OUTPUT    ::zg::GraphicsEngine::UseGraphicsLogger().debug()
#define GFX_WARN_OUTPUT     ::zg::GraphicsEngine::UseGraphicsLogger().warn()
#define GFX_ERROR_OUTPUT    ::zg::GraphicsEngine::UseGraphicsLogger().error()
#define GFX_CRITICAL_OUTPUT ::zg::GraphicsEngine::UseGraphicsLogger().critical()

#define GFX_LOG_INFO(...)     ::zg::GraphicsEngine::UseGraphicsLogger().info().logLine(__VA_ARGS__)
#define GFX_LOG_DEBUG(...)    ::zg::GraphicsEngine::UseGraphicsLogger().debug().logLine(__VA_ARGS__)
#define GFX_LOG_WARN(...)     ::zg::GraphicsEngine::UseGraphicsLogger().warn().logLine(__VA_ARGS__)
#define GFX_LOG_ERROR(...)    ::zg::GraphicsEngine::UseGraphicsLogger().error().logLine(__VA_ARGS__)
#define GFX_LOG_CRITICAL(...) ::zg::GraphicsEngine::UseGraphicsLogger().critical().logLine(__VA_ARGS__)

#include <zucchini/zucchini.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/scalar_multiplication.hpp>

#endif // ZG_DEFINES_HPP

