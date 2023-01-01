#ifndef HL_PATTERNCONFIGREGISTRY_H
#define HL_PATTERNCONFIGREGISTRY_H

#include "humblelogging/defines.h"
#include "humblelogging/util/ternarytree.h"
#include <string>

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API PatternConfigRegistry
{
public:
	PatternConfigRegistry();
	PatternConfigRegistry(const PatternConfigRegistry&) = delete;
	PatternConfigRegistry& operator=(const PatternConfigRegistry&) = delete;
	~PatternConfigRegistry();

	bool loadFromFile(const std::string& filepath);
	bool loadFromString(const std::string& buffer);
	bool load(std::istream& istream);

	void insert(const std::string& pattern, int level);

	int getLogLevel(const std::string& loggerName) const;

private:
	struct Entry
	{
		std::string pattern;
		bool recursive;
		int level;
	};
	TernaryTree<Entry*> _tree;
	int _defaultLogLevel;
};

HL_NAMESPACE_END
#endif