#include "humblelogging/appender.h"
#include "humblelogging/formatter.h"
#include <cassert>

HL_NAMESPACE_BEGIN

Appender::Appender()
{}

Appender::~Appender()
{}

void Appender::setFormatter(std::unique_ptr<Formatter> formatter)
{
	assert(formatter);

	std::lock_guard lock(_mutex);
	_formatter = std::move(formatter);
}

HL_NAMESPACE_END