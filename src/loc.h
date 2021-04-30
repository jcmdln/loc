// loc.h
#ifndef loc_h
#define loc_h

#include <err.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#ifndef __dead
#include <sys/cdefs.h>
#endif

#ifndef __dead
#define __dead __attribute__((noreturn))
#endif

#ifndef MAXBSIZE
#define MAXBSIZE sizeof(char)
#endif

extern char *__progname;

#endif
