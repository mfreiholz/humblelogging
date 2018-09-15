#ifndef HL_ROLLINGFILEAPPENDER_H
#define HL_ROLLINGFILEAPPENDER_H

#include "humblelogging/appender.h"
#include "humblelogging/util/mutex.h"

#include <fstream>

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API RollingFileAppender
	: public Appender
{
public:
	RollingFileAppender(const std::string& filename, bool immediate = false, int maxRoll = 5, unsigned long maxFileSize = 10485760);
	virtual ~RollingFileAppender();
	virtual void log(const LogEvent& logEvent);

protected:
	/*
    Implements the usual roll over behavior.
    Renames files "file.log.1" => "file.log.2", ...

    TODO: We may want to keep the modification time of the old files,
    which currently gets lost through renaming.

    \pre _mutex.lock()

    \return Returns "true" if the file stream is open and can be used for logging.
  */
	bool roll();

private:
	Mutex _mutex;
	std::string _filename;
	bool _immediate;
	int _maxRoll;
	unsigned long _maxFileSize;

	std::ofstream _stream;
};

HL_NAMESPACE_END
#endif
