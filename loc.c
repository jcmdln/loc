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
	
	char *ch;
	ssize_t len;
	int64_t lines_total;
	
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
	
	while ((len = read(fd, buf, MAXBSIZE)) > 0 ) {
		for (ch = buf; len--; ++ch)
			if (*ch == '\n')
				++lines_total;
	}
	
	printf("total: %d\n", lines_total);

	return 0;
}

int
main(int argc, char **argv)
{
	if (pledge("stdio rpath", NULL) == -1)
		err(1, "pledge");

	int opt;

	setlocale(LC_CTYPE, "");

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

	if (!*argv) {
		loc_count(NULL);
	} else {
		do {
			loc_count(*argv);
		} while(*++argv);
	}
	
	return 0;
}
