// Platform detection
#if defined(_WIN32) // Windows

   #if defined(_WIN64)
      #define ZG_PLATFORM_WINDOWS

      #ifdef _MSC_VER
         #pragma warning(disable: 4251)
      #endif
   #else
      #error "32-bit platforms not supported !"
   #endif

#elif defined(__ANDROID__) // Android
   
   #define ZG_PLATFORM_ANDROID
   #error "Android platform not supported !"

#elif defined(__linux__) // Linux

   #if defined(__x86_64__) || defined(__aarch64__)
      #define ZG_PLATFORM_LINUX
   #else
      #error "32-bit platforms not supported !"
   #endif

#elif defined(__APPLE__) || defined(__MACH__) // MacOS

   #include <TargetConditionals.h>

   #if TARGET_OS_IPHONE == 1
      #define ZG_PLATFORM_IOS
      #error "iOS platform not supported !"
   #elif TARGET_OS_MAC == 1
      #define ZG_PLATFORM_MACOS
   #else
      #error "Unsupported Apple platform"
   #endif

#else

   #error "Unsupported platform or architecture !"

#endif // Platform detection

#if __GNUC__ >= 4 || defined(__clang__)// GNU GCC __attribute__

   #define ZG_API __attribute__ ((__visibility__("default")))
   #define ZG_DETAIL __attribute__ ((__visibility__("hidden")))

#else // idk

   #define ZG_API
   #define ZG_DETAIL

#endif // DLL/SO specifiers
