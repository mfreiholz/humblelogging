#ifndef HL_FMT_H
#define HL_FMT_H
#include <cstring>
#include <memory>
#include <stdio.h>

// Formats the given string `format` with parameters from `args`.
// Uses same syntax as `printf()`.
// template<typename... Args>
// std::string str_fmt(const std::string& format, Args... args)
// {
// 	size_t size = snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
// 	std::unique_ptr<char[]> buf(new char[size]);
// 	std::snprintf(buf.get(), size, format.c_str(), args...);
// 	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
// }

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

#endif