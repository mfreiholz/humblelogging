#ifndef HL_FILEAPPENDER_H
#define HL_FILEAPPENDER_H

#include "humblelogging/appender.h"
#include <fstream>
#include <mutex>

HL_NAMESPACE_BEGIN

/*
	Writes all events to a defined file.
	The file will never be overwritten, instead everything will be appended.

	Note: There is no limit in file size. The file will grow without limit.
*/
class HUMBLE_EXPORT_API FileAppender
	: public Appender
{
public:
	/*
		Opens the file-handle to `filename`.

		\param[in] filename
			Absolute file path.
		\param[in] immediate
			If the `true` the output stream will be flushed with every call to `log(...)` - unbuffered.
	*/
	FileAppender(const std::string& filename, bool immediate = false);

	/*
		Closes the file-handle.
	*/
	~FileAppender() override;

	void log(const LogEvent& logEvent) override;

private:
	std::mutex _mutex;
	std::ofstream _stream;
	bool _immediate;
};

HL_NAMESPACE_END
#endif