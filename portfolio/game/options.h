#ifndef __OPTIONS_INCLUDED__
#define __OPTIONS_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

extern int ProcessOptions(int argc, char **argv);
extern void Fatal(char *fmt, ...);
//extern void runOptions(int argc, char **argv);

#endif
