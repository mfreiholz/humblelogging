#include "humblelogging/util/patternconfigregistry.h"
#include "humblelogging/loglevel.h"
#include <fstream>
#include <istream>
#include <sstream>

HL_NAMESPACE_BEGIN

PatternConfigRegistry::PatternConfigRegistry()
	: _defaultLogLevel(LogLevel::Off)
{
}

PatternConfigRegistry::PatternConfigRegistry(const PatternConfigRegistry& other)
{
	_tree = other._tree;
	_defaultLogLevel = other._defaultLogLevel;
}

PatternConfigRegistry::~PatternConfigRegistry()
{
	// TODO Delete Entry* objects of _tree.
}

bool PatternConfigRegistry::loadFromFile(const std::string& filepath)
{
	std::ifstream in;
	in.open(filepath.c_str(), std::ifstream::binary); // TODO Handle exception?
	if (in.fail() || !in.is_open())
	{
		return false;
	}
	return load(in);
}

bool PatternConfigRegistry::loadFromString(const std::string& buffer)
{
	std::istringstream in(buffer, std::ios_base::in);
	return load(in);
}

bool PatternConfigRegistry::load(std::istream& in)
{
	char buff[4096];
	while (!in.eof() && !in.bad())
	{
		in.getline(buff, 4096);
		std::string line(buff);
		line.erase(line.find_last_not_of(" \n\r\t") + 1);

		// Skip empty lines.
		if (line.empty())
			continue;

		// Skip comments.
		bool skip = false;
		for (std::string::size_type i = 0; i < line.length(); ++i)
		{
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
		if ((pos = line.find_last_of('=')) == std::string::npos)
		{
			continue; // Invalid line.
		}
		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1);

		// Extract logger name pattern from <key>.
		std::string pattern = "";
		if ((pos = key.find('(')) != std::string::npos)
		{
			std::size_t pos2 = key.find_last_of(')');
			if (pos2 != std::string::npos)
			{
				pattern = key.substr(pos + 1, pos2 - (pos + 1));
			}
			key = key.substr(0, pos);
		}

		if (key.find("logger.level") == 0)
		{
			const int level = LogLevel::resolveLogLevel(value);
			insert(pattern, level);
		}
	}
	return true;
}

void PatternConfigRegistry::insert(const std::string& ppattern, int level)
{
	// Insert into lookup tree.
	std::string pattern = ppattern;
	std::size_t pos = std::string::npos;
	bool recursive = false;
	if ((pos = pattern.find('*')) == pattern.length() - 1)
	{
		pattern.erase(pos);
		recursive = true;
	}

	char* treeKey = &(*const_cast<char*>(pattern.c_str()));
	TernaryNode<Entry*>* node = _tree.findNodeEnd(treeKey);
	Entry* entry = NULL;
	if (!node)
		entry = new Entry;
	else
		entry = node->_value;
	entry->pattern = pattern;
	entry->recursive = recursive;
	entry->level = level;

	if (!node)
	{
		treeKey = &(*const_cast<char*>(pattern.c_str()));
		_tree.insert(treeKey, entry);
	}

	// Change the "_defaultLogLevel" in case of *-pattern.
	if (pattern.empty() && recursive)
		_defaultLogLevel = level;
}

int PatternConfigRegistry::getLogLevel(const std::string& loggerName) const
{
	char* key = &(*const_cast<char*>(loggerName.c_str()));

	TernaryTree<Entry*>::FindNodePathData data;
	TernaryNode<Entry*>* node = _tree.findNodePath(key, data);
	if (node && node->_end)
	{
		return node->_value->level;
	}

	// Search the first recursive Entry (backwards).
	std::vector<TernaryNode<Entry*>*>::reverse_iterator itr, iend = data._nodes.rend();
	for (itr = data._nodes.rbegin(); itr != iend; ++itr)
	{
		TernaryNode<Entry*>* node = (*itr);
		if (!node->_end || !node->_value->recursive)
			continue;
		return node->_value->level;
	}

	return _defaultLogLevel;
}

HL_NAMESPACE_END
