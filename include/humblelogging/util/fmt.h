#ifndef HL_FMT_H
#define HL_FMT_H

#include <memory>
#include <stdio.h>
#include <string>

HL_NAMESPACE_BEGIN

/*
	Formats the given string "fmt", which is the first parameter,
	with values from other paramteres.
	See `printf()`, it shares same signatures.
*/
template<typename... Args>
std::string strfmt(Args... args)
{
	const int size = snprintf(nullptr, 0, args...) + 1; // Extra space for '\0'
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, args...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

HL_NAMESPACE_END
#endif