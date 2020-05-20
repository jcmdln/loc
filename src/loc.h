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

// comments
struct
comments {
	char *single;
	char *open;
	char *close;
};

// counts is a struct containing the count of various lines.
struct
counts {
	uint32_t blank;
	uint32_t code;
	uint32_t comment;
	uint32_t files;
};

// lang
struct
lang {
	char *name;
	char *ext;
	struct comments comments;
	struct counts counts;
	struct lang *next;
};

// langs is a linked list of initialized languages.
extern struct lang *
langs;

// loc_langs_init
struct lang *
loc_langs_init(struct lang *l, char *ext);

// loc_parse
int
loc_parse(struct lang *l, int fd, char *buf);

// loc_results
int
loc_results();

// loc_seek
int
loc_seek(char *ext);
