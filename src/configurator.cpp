#include "humblelogging/configurator.h"

#include <fstream>

#include "humblelogging/loglevel.h"

namespace humble {
namespace logging {

///////////////////////////////////////////////////////////////////////////////
// Configurator
///////////////////////////////////////////////////////////////////////////////

Configurator::Configurator()
  : _defaultLogLevel(LogLevel::All)
{

}

Configurator::~Configurator()
{

}

///////////////////////////////////////////////////////////////////////////////
// NullAppender
///////////////////////////////////////////////////////////////////////////////

DefaultConfigurator::DefaultConfigurator()
  : Configurator()
{

}

DefaultConfigurator::~DefaultConfigurator()
{

}

void DefaultConfigurator::configure(Logger *l)
{

}

DefaultConfigurator* DefaultConfigurator::fromFile(const std::string &filepath)
{
  std::ifstream in;
  in.open(filepath.c_str(), std::ifstream::binary); // TODO Handle exception?
  if (in.is_open()) {
    // Get length of file.
    in.seekg(0, in.end);
    std::streamoff fileLength = in.tellg();
    in.seekg(0, in.beg);

    // Allocate buffer for file content.
    char *buffer = new char[fileLength];
    in.read(buffer, fileLength);
    delete[] buffer;
  }
  return new DefaultConfigurator();
}

}}  // End of namespace.
