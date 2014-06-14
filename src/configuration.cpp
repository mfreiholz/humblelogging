#include "humblelogging/configuration.h"

#include <fstream>

#include "humblelogging/loglevel.h"

namespace humble {
namespace logging {

///////////////////////////////////////////////////////////////////////////////
// Configuration
///////////////////////////////////////////////////////////////////////////////

Configuration::Configuration()
{

}

Configuration::~Configuration()
{

}

///////////////////////////////////////////////////////////////////////////////
// DefaultConfiguration
///////////////////////////////////////////////////////////////////////////////

DefaultConfiguration::DefaultConfiguration()
  : Configuration()
{

}

DefaultConfiguration::~DefaultConfiguration()
{

}

int DefaultConfiguration::getLogLevel(Logger *logger, Appender *appender) const 
{
  return LogLevel::All;
}

///////////////////////////////////////////////////////////////////////////////
// DefaultConfiguration
///////////////////////////////////////////////////////////////////////////////

FileConfiguration::FileConfiguration(const std::string &filepath)
  : Configuration()
{
  load(filepath);
}

FileConfiguration::~FileConfiguration()
{
  // TODO clear _tree.
}

int FileConfiguration::getLogLevel(Logger *logger, Appender *appender) const
{
  return 0;
}

bool FileConfiguration::load(const std::string &filepath)
{
  std::ifstream in;
  in.open(filepath.c_str(), std::ifstream::binary); // TODO Handle exception?
  if (in.fail() || !in.is_open()) {
    return false;
  }

  char buff[4096];
  while (!in.eof() && !in.bad()) {
    in.getline(buff, 4096);
    std::string line(buff);
    line.erase(line.find_last_not_of(" \n\r\t") + 1);

    // Skip empty lines.
    if (line.empty())
      continue;

    // Skip comments.
    bool skip = false;
    for (std::string::size_type i = 0; i < line.length(); ++i) {
      if (line[i] == ' ' || line[i] == '\t')
        continue;
      else if (line[i] == '#')
        skip = true;
      break;
    }
    if (skip)
      continue;

    // Separate <key>=<value>.
    std::size_t pos = std::string::npos;
    if ((pos = line.find_last_of('=')) == std::string::npos) {
      continue; // Invalid line.
    }
    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);

    // Extract logger name pattern from <key>.
    std::string loggerNamePattern = "";
    if ((pos = key.find('(')) != std::string::npos) {
      std::size_t pos2 = key.find_last_of(')');
      if (pos2 != std::string::npos) {
        loggerNamePattern = key.substr(pos + 1, pos2 - (pos + 1));
      }
      key = key.substr(0, pos);
    }

    // Insert into lookup tree.
    bool recursive = false;
    if ((pos = loggerNamePattern.find('*')) == loggerNamePattern.length() - 1) {
      loggerNamePattern.erase(pos);
      recursive = true;
    }

    char *treeKey = &(*const_cast<char*>(loggerNamePattern.c_str()));
    TernaryNode<Entry*> *node = _tree.findNodeEnd(treeKey);
    Entry *entry = 0;
    if (!node)
      entry = new Entry;
    else
      entry = node->_value;
    entry->pattern = loggerNamePattern;
    entry->recursive = recursive;

    if (key.find("logger.level") == 0) {
      entry->level = LogLevel::resolveLogLevel(value);
    }

    if (!node) {
      treeKey = &(*const_cast<char*>(loggerNamePattern.c_str()));
      _tree.insert(treeKey, entry);
    }

    printf("[key=%s] [value=%s] [logger=%s]\n", key.c_str(), value.c_str(), loggerNamePattern.c_str());
  }
  return true;
}

//// Get length of file.
//in.seekg(0, in.end);
//std::streamoff fileLength = in.tellg();
//in.seekg(0, in.beg);
//
//// Read entire file into buffer.
//char *buffer = new char[fileLength];
//in.read(buffer, fileLength);
//in.close();
//delete[] buffer;

}}  // End of namespace.
