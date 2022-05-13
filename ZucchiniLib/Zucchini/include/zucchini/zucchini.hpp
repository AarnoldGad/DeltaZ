/**
 * zucchini.hpp
 * 27 Nov 2020
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2022 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZUCCHINI_HPP
#define ZUCCHINI_HPP

#include <zucchini/defines.hpp>

// Backtrace
#include <zucchini/Backtrace/CallStack.hpp>
#include <zucchini/Backtrace/StackFrame.hpp>

// Logger
#include <zucchini/Log/Logger.hpp>
#include <zucchini/Log/Writer.hpp>
#include <zucchini/Log/ConsoleWriter.hpp>
#include <zucchini/Log/FileWriter.hpp>
#include <zucchini/Log/StreamWriter.hpp>

// Debug
#include <zucchini/Exception/Exception.hpp>
#include <zucchini/Debug/Assert.hpp>
#include <zucchini/Debug/Tee.hpp>
#include <zucchini/Debug/TodoBefore.hpp>

// Math
#include <zucchini/Math/Angle.hpp>
#include <zucchini/Math/RangedNumeric.hpp>
#include <zucchini/Math/Math.hpp>

// Event System
#include <zucchini/Event/Event.hpp>
#include <zucchini/Event/EventDispatcher.hpp>
#include <zucchini/Event/EventBus.hpp>
#include <zucchini/Event/EventSubscriber.hpp>

// Signal System
#include <zucchini/Signal/Signal.hpp>
#include <zucchini/Signal/Listener.hpp>

// Resource Management
#include <zucchini/Resource/ResourceManager.hpp>

// Memory Management
#include <zucchini/Memory/Allocator.hpp>
#include <zucchini/Memory/New.hpp>
#include <zucchini/Memory/StandardAllocator.hpp>

// Time management
#include <zucchini/Time/Chrono.hpp>
#include <zucchini/Time/Date.hpp>
#include <zucchini/Time/Time.hpp>

// Streams
#include "zucchini/Stream/OutputStream.hpp"
#include "zucchini/Stream/FileOutputStream.hpp"

// Common
#include <zucchini/Common/Arguments.hpp>
#include <zucchini/Common/Console.hpp>
#include <zucchini/Common/Functor.hpp>
#include <zucchini/Common/Observer.hpp>
#include <zucchini/Common/Random.hpp>
#include <zucchini/Common/System.hpp>
#include <zucchini/Common/NamedType.hpp>
#include <zucchini/Common/CRTP.hpp>

// Utils
#include <zucchini/Util/StringUtils.hpp>
#include <zucchini/Util/FileUtils.hpp>

#endif // ZUCCHINI_HPP
