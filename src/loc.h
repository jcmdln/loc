/* loc.h
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include <sys/param.h>
#include <sys/stat.h>

#include <ctype.h>
#include <err.h>
#include <getopt.h>
#include <fcntl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef MAXBSIZE
#define MAXBSIZE 8192 // very arbitrary, and likely never correct.
#endif

#ifndef uint32_t
#include <stdint.h>
#endif

extern char *__progname;

struct comments {
	char *single;
	char *open;
	char *close;
};

struct counts {
	uint32_t blank;
	uint32_t code;
	uint32_t comment;
	uint32_t files;
};

struct lang {
	char *name;
	char *ext;
	struct comments comments;
	struct counts counts;
	void *next;
};

extern struct lang langs[7];

int
loc_langs_init(char *ext);

int
loc_parse(int i, int fd, char *buf);

int
loc_results();

int
loc_seek(char *ext);
