/* loc.h
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include <sys/param.h>
#include <sys/stat.h>

#include <ctype.h>
#include <err.h>
#include <fcntl.h>
#include <getopt.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef MAXBSIZE
#define MAXBSIZE 1024 /* very arbitrary, and likely never correct */
#endif

#ifndef uint32_t
#include <stdint.h>
#endif

extern char *__progname;

/*
 * comments
 */
struct comments {
	char *single;
	char *open;
	char *close;
};

/*
 * counts is a struct containing the count of various lines of code.
 */
struct counts {
	uint32_t blank;
	uint32_t code;
	uint32_t comment;
	uint32_t files;
};

/*
 * langs is a struct containing the definition of a language, including
 * its rules for parsing comments and counts of lines of code.
 */
struct langs {
	char *name;
	char *ext;
	struct comments comment;
	struct counts count;
	struct langs *next;
};

extern struct langs *lang;

struct langs *loc_langs_init(struct langs *lang, char *ext);

int loc_parse(struct langs *lang, int file, char *buffer);

int loc_results();

int loc_seek(char *ext);
