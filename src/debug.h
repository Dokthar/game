#ifndef DEBUG_H
#define DEBUG_H


#define DEBUG


#ifdef DEBUG
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void dbg_printf(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stdout, "Debug:");
	vfprintf(stdout, fmt, args);
	va_end(args);
}
#else
void dbg_printf(const char *fmt, ...) { (void)fmt; }
#endif

#endif
