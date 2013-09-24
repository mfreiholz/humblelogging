#ifndef HUMBLE_DEFINES_HEADER
#define HUMBLE_DEFINES_HEADER

// DLL Import/Export macro
#ifdef WIN32
  #if defined(HUMBLE_LOGGING_EXPORT)
    #define HUMBLE_EXPORT_API __declspec(dllexport)
  #else
    #define HUMBLE_EXPORT_API
  #endif
#else
  #define HUMBLE_EXPORT_API
#endif

#endif
