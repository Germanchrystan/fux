#pragma once

#ifdef _WIN32
  #if defined(BUILDING_DLL)
    #define EXPORT __declspec(dllexport)
  #else
    #define EXPORT __declspec(dllimport)
  #endif
#else
  #define EXPORT __attribute__((visibility("default")))
#endif
