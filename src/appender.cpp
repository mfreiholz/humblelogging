#include "humblelogging/appender.h"
#include "humblelogging/formatter.h"
#include "humblelogging/loglevel.h"
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

HL_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// Appender
///////////////////////////////////////////////////////////////////////////////

Appender::Appender()
	: _formatter(NULL)
{
}

Appender::~Appender()
{
	if (_formatter)
	{
		delete _formatter;
		_formatter = NULL;
	}
}

void Appender::setFormatter(Formatter* formatter)
{
	MutexLockGuard lock(_mutex);
	if (_formatter)
	{
		delete _formatter;
		_formatter = NULL;
	}
	_formatter = formatter;
}

Formatter* Appender::getFormatter() const
{
	MutexLockGuard lock(_mutex);
	return _formatter;
}

HL_NAMESPACE_END
