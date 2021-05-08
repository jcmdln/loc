// loc.h
#ifndef loc_h
#define loc_h

#include <sys/types.h>

#ifndef __dead
#include <sys/cdefs.h>
#endif

#include <err.h>
#include <fcntl.h>
#include <getopt.h>
#include <locale.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <wchar.h>

#ifndef __dead
#define __dead __attribute__((noreturn))
#endif

#ifndef MAXBSIZE
#define MAXBSIZE sizeof(uint32_t)
#endif

extern char *__progname;

#endif
