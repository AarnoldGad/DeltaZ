#ifndef ZE_PCH_HPP
#define ZE_PCH_HPP

#include "zucchini/platform.hpp"

// Streams
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

// Collections
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

// Misc
#include <memory>
#include <functional>
#include <algorithm>
#include <utility>
#include <thread>
#include <random>
#include <type_traits>
#include <chrono>
#include <initializer_list>

// Legacy C
#include <cstdint>
#include <cctype>
#include <ctime>
#include <cassert>
#include <cstdlib>
#include <cstdio>

// Platform specifics
#if defined(ZE_PLATFORM_WINDOWS)
   #include <Windows.h>

   #undef min
   #undef max
#elif defined(ZE_PLATFORM_LINUX) || defined(ZE_PLATFORM_MACOS)
   #include <sys/utsname.h>
   #include <dlfcn.h>
#endif

#endif // ZE_PCH_HPP

