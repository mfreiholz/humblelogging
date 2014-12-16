#ifndef HUMBLE_DEFINES_HEADER
#define HUMBLE_DEFINES_HEADER

// DLL Import/Export macro
#ifdef _WIN32
  #if defined(HUMBLELOGGING_EXPORT)
    #define HUMBLE_EXPORT_API __declspec(dllexport)
  #else
    #define HUMBLE_EXPORT_API __declspec(dllexport)
  #endif
#else
  #define HUMBLE_EXPORT_API
#endif

// Namespace defines
#define HL_NAMESPACE_BEGIN \
  namespace humble { \
  namespace logging {

#define HL_NAMESPACE_END \
  }}

// Disable copy constructor.
#define HUMBLE_DISABLE_COPY(Class) \
  Class(const Class &other);

// Disable warning on MSVC
#ifdef _MSC_VER
  #pragma warning (disable:4251)
  #pragma warning (disable:4996) // sprintf => sprintf_s
#endif

// Function name for LogEvent
#if defined(_MSC_VER)
  #define __FUNCNAME__ __FUNCSIG__
#elif defined(__GNUC__)
  #define __FUNCNAME__ __PRETTY_FUNCTION__
#endif

#endif // HUMBLE_DEFINES_HEADER
