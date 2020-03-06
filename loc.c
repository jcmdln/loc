/* loc.c - Summarize the lines of code within a directory
 *
 * Copyright 2020 Johnathan C. Maudlin <jcmdln@gmail.com>
 */

#include <sys/param.h>
#include <sys/stat.h>

#include <err.h>
#include <fcntl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *__progname;

int opt_blank;
int opt_code;
int opt_comment;

struct loc {
	int64_t blank;
	int64_t code;
	int64_t comment;
};

struct lang {
	char *name;
	int64_t files;
	struct loc lines;
};

struct lang C = {"C", 0, {0, 0, 0}};
struct lang Makefile = {"Makefile", 0, {0, 0, 0}};

int
results()
{
	printf("%-24s  %10s  %10s  %10s  %10s\n",
	       "language", "files", "blank", "comment", "code");
	printf("%-24s  %10lld  %10lld  %10lld  %10lld\n",
	       C.name, C.files, C.lines.blank, C.lines.comment,
	       C.lines.code);
	return 0;
}

int
lang_c(int fd, char *buf)
{
	char *ch = ""; // character
	char *lc = ""; // last character
	int in_comment = 0;
	ssize_t len;

	while ((len = read(fd, buf, MAXBSIZE)) > 0) {
		for (ch = buf; len--; ++ch) {
			if (*lc == '/' && *ch == '*')
				in_comment = 1;

			if (*ch == '\n') {
				if (*lc == '\n')
					++C.lines.blank;
				if (in_comment)
					++C.lines.comment;
				if (!in_comment && *lc != '\n')
					++C.lines.code;
			}

			if (in_comment && *lc == '*' && *ch == '/') {
				in_comment = 0;
				++C.lines.comment;
			}

			lc = ch;
		}
	}

	return 0;
}

int
main(int argc, char **argv)
{
	static char *buf;
	static size_t bufsz;
	int fd;
	int opt;

	setlocale(LC_CTYPE, "");

	if (pledge("rpath stdio", NULL) == -1)
		err(1, "pledge");

	while ((opt = getopt(argc, argv, "bcCt")) != -1) {
		switch (opt) {
		default:
			fprintf(stderr,
				"usage: %s [-bcCht] [file ...]\n",
				__progname);
			return 1;
		}
	}
	argv += optind;
	argc -= optind;

	if (argc > 0) {
		do {
			if ((fd = open(*argv, O_RDONLY, 0)) == -1) {
				warn("%s", *argv);
				return 1;
			}

			if (bufsz < MAXBSIZE &&
			    (buf = realloc(buf, MAXBSIZE)) == NULL) {
				err(1, NULL);
			}

			++C.files;
		        lang_c(fd, buf);
		} while(*++argv);

		results();
	}

	return 0;
}
