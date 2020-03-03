/* loc.c - Show statistics about lines of code.
 *
 */

#include <sys/param.h>
#include <sys/stat.h>

#include <err.h>
#include <fcntl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char *__progname;

int fd;

int opt_blank;
int opt_code;
int opt_comment;
int opt_total;

static int
loc_count(char *file)
{
	static char *buf;
	static size_t bufsz;

	char *c;
	char *lc;
	ssize_t len;

	int64_t lines_blank = 0;
	int64_t lines_code = 0;
	int64_t lines_comment = 0;
	int64_t lines_total = 0;

	if (file) {
		if ((fd = open(file, O_RDONLY, 0)) == -1) {
			warn("%s", file);
			return 1;
		}
	}

	if (bufsz < MAXBSIZE &&
	    (buf = realloc(buf, MAXBSIZE)) == NULL) {
		err(1, NULL);
	}

	int comment = 0;
	while ((len = read(fd, buf, MAXBSIZE)) > 0) {
		for (c = buf; len--; ++c) {
			if (comment > 0) {
				if (*c == '/' && *lc == '*') {
				        comment = 0;
					++lines_comment;
				}
			}

			if (!comment && *c == '*' && *lc == '/')
				comment = 1;

			if (*c == '\n') {
				if (comment > 0)
					++lines_comment;

				if (*lc == '\n')
					++lines_blank;

				if (*lc != '\n' && !comment)
					++lines_code;

				++lines_total;
			}

			lc = c;
		}
	}

	printf("File Extension\tBlank\tComment\tCode\tTotal\n");
	printf("%-15s\t%lld\t%lld\t%lld\t%lld\n", file,
	       lines_blank, lines_comment, lines_code, lines_total);

	return 0;
}

int
main(int argc, char **argv)
{
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
			loc_count(*argv);
		} while(*++argv);
	}

	return 0;
}
