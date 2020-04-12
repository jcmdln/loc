/* loc.c - Summarize the lines of code within a file or directory
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
#include <string.h>
#include <unistd.h>

char *__progname;

uint32_t opt_blank;
uint32_t opt_code;
uint32_t opt_comment;

struct loc {
	uint64_t blank;
	uint64_t code;
	uint64_t comment;
	uint64_t total;
};

struct lang {
	char *name;
	uint64_t files;
	struct loc lines;
};

struct lang C;

int
results()
{
        printf("%-24s  %10s  %10s  %10s  %10s\n",
	       "language", "files", "blank", "comment", "code");
	printf("%-24s  %10llu  %10llu  %10llu  %10llu\n",
	       C.name, C.files, C.lines.blank, C.lines.comment,
	       C.lines.code);

	return 0;
}

int
lang_c(int fd, char *buf)
{
	char *ch; // character
	char *lc = ""; // last character
	uint in_comment = 0;
	ssize_t len;

	C.name = "C";

        if ((len = read(fd, buf, MAXBSIZE)) > 0) {
		for (ch = buf; len--; ++ch) {
			switch (*ch) {
			case '\n':
				if (in_comment) {
					++C.lines.comment;
				} else if (*lc == '\n') {
					++C.lines.blank;
				}

				++C.lines.total;
				break;
			case '*':
				if (*lc == '/')
					in_comment = 1;
			case '/':
				if (in_comment) {
					if (*lc == '*') {
						in_comment = 0;
						++C.lines.comment;
					}
				}
			}

			lc = ch;
		}

		C.lines.code = ((C.lines.total - C.lines.blank)
				- C.lines.comment);
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

			if (strstr(*argv, ".c") != NULL) {
				lang_c(fd, buf);
				++C.files;
			} else {
				printf("error: '%s' not implemented\n",
				       *argv);
			}

		} while(*++argv);

		if (C.lines.total > 0) {
			results();
		}
	}

	return 0;
}
