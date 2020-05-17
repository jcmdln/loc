/* loc.h
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include <sys/param.h>
#include <sys/stat.h>

#include <err.h>
#include <getopt.h>
#include <fcntl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef MAXBSIZE
#define MAXBSIZE 8192 // very arbitrary, and likely never correct.
#endif

#ifndef uint64_t
#include <stdint.h>
#endif

extern char *__progname;

struct loc {
	uint32_t blank;
	uint32_t code;
	uint32_t comment;
	uint32_t total;
};

struct lang {
	char *name;
	char *ext;
	char *comment_single;
	char *comment_multi_start;
	char *comment_multi_end;
	uint32_t files;
	struct loc lines;
};

extern struct lang langs[7];

int
loc_langs_init();

int
loc_parse(int i, int fd, char *buf);

int
loc_results();

int
loc_seek(char *ext);
