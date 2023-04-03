#ifndef HL_ROLLINGFILEAPPENDER_H
#define HL_ROLLINGFILEAPPENDER_H

#include "humblelogging/appender.h"
#include <cinttypes>
#include <fstream>

HL_NAMESPACE_BEGIN

/*
	\brief Writes all logs to a rolling file.
*/
class HUMBLE_EXPORT_API RollingFileAppender
	: public Appender
{
public:
	/*
		Constructor.

		\param[in] filename
			Path to log file.
		\param[in] immediate
			If enabled the log gets written to file immediately instead of using OS buffering.
		\param[in] maxRoll
			Maximum number of files in roll rotation.
		\param[in] maxFileSize
			Maximum size in bytes of a log file before a new file is created.
	*/
	RollingFileAppender(const std::string& filename, bool immediate = false, int maxRoll = 5, uint64_t maxFileSize = 10485760);

	/*
	*/
	~RollingFileAppender() override;

	/*
	*/
	void log(const LogEvent& logEvent) override;

protected:
	/*
		Implements the usual roll over behavior.
		Renames files "file.log.1" => "file.log.2", ...

		TODO: We may want to keep the modification time of the old files,
		which currently gets lost through renaming.

		\pre Appender::_mutex.lock()

		\return Returns "true" if the file stream is open and can be used for logging.
	*/
	bool roll();

private:
	std::string _filename;
	bool _immediate;
	int _maxRoll;
	uint64_t _maxFileSize;
	std::ofstream _stream;
};

HL_NAMESPACE_END
#endif