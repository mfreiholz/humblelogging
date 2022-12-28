#ifndef HL_ROLLINGFILEAPPENDER_H
#define HL_ROLLINGFILEAPPENDER_H

#include "humblelogging/appender.h"
#include "humblelogging/util/mutex.h"
#include <cinttypes>
#include <fstream>

HL_NAMESPACE_BEGIN

/*
	TODO
*/
class HUMBLE_EXPORT_API RollingFileAppender
	: public Appender
{
public:
	/*
		TODO

		\param[in] filename
			TODO
		\param[in] immediate
			TODO
		\param[in] maxRoll
			TODO
		\param[in] maxFileSize
			TODO
	*/
	RollingFileAppender(const std::string& filename, bool immediate = false, int maxRoll = 5, uint64_t maxFileSize = 10485760);

	/*
		TODO
	*/
	~RollingFileAppender() override;

	void log(const LogEvent& logEvent) override;

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
	uint64_t _maxFileSize;

	std::ofstream _stream;
};

HL_NAMESPACE_END
#endif
