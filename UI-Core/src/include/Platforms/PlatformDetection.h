#ifndef GUI_CORE_DETECTOR
#define GUI_CORE_DETECTOR

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  // Libs
  #pragma comment(lib, "gdi32.lib")
  #pragma comment(lib, "user32.lib")
  #pragma comment(lib, "shell32.lib")

  #define UI_CORE_PLATFORM_WINDOWS

  #ifdef _WIN64
  #else
  
  #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #define UI_CORE_PLATFORM_APPLE
    
    #if TARGET_IPHONE_SIMULATOR
      // iOS, tvOS, or watchOS Simulator
    #elif TARGET_OS_MACCATALYST
      // Mac's Catalyst (ports iOS API into Mac, like UIKit).
    #elif TARGET_OS_IPHONE
      
    #elif TARGET_OS_MAC
    #define UI_CORE_PLATFORM_APPLE_MACOS

    #else
      #error "Unknown Apple platform"
    #endif
#elif __linux__
  #define UI_CORE_PLATFORM_LINUX
#elif __unix__ // all unices not caught above

#elif defined(_POSIX_VERSION)

#else
  #error "Unknown compiler"
#endif

#endif