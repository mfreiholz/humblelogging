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

// Namespace defines
#define HUMBLE_NAMESPACE_BEGIN \
  namespace humble { \
  namespace logging {

#define HUMBLE_NAMESPACE_END \
  }}

// Disable copy constructor.
#define HUMBLE_DISABLE_COPY(Class) \
  Class(const Class &other);

// Disable warning on MSVC
#ifdef _MSC_VER
  #pragma warning (disable:4251)
#endif

#endif
