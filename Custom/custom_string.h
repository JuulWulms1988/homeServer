#pragma once
#ifdef _WIN32
#include <string>
#endif
#ifndef _WIN32
#include <stdio.h>
#include <string.h>
inline void strncpy_s(char* dest, size_t dSize, const char* source, size_t srcSize) {
	strncpy(dest, source, srcSize);
	dest[srcSize] = '\0';
}
#endif