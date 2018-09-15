#ifndef HL_FILEAPPENDER_H
#define HL_FILEAPPENDER_H

#include "humblelogging/appender.h"
#include "humblelogging/util/mutex.h"

#include <fstream>

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API FileAppender
	: public Appender
{
public:
	FileAppender(const std::string& filename, bool immediate = false);
	virtual ~FileAppender();
	virtual void log(const LogEvent& logEvent);

private:
	Mutex _mutex;
	std::ofstream _stream;
	bool _immediate;
};

HL_NAMESPACE_END
#endif
