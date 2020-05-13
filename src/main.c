/* loc.c - Summarize the lines of code within a file or directory
 *
 * Copyright 2020 Johnathan C. Maudlin <jcmdln@gmail.com>
 */

#include <string.h>

#include "loc.h"

uint32_t opt_blank;
uint32_t opt_code;
uint32_t opt_comment;

int
loc_results()
{
	printf("%-24s  %10s  %10s  %10s  %10s\n",
	       "language", "files", "blank", "comment", "code");

	for (int i = 0; i <= 1; i++) {
		if (langs[i].files < 1 || langs[i].name == NULL)
			continue;

#ifdef __OpenBSD__
		printf("%-24s  %10llu  %10llu  %10llu  %10llu\n",
		       langs[i].name,
		       langs[i].files,
		       langs[i].lines.blank,
		       langs[i].lines.comment,
		       langs[i].lines.code);
#else
		printf("%-24s  %10lu  %10lu  %10lu  %10lu\n",
		       langs[i].name,
		       langs[i].files,
		       langs[i].lines.blank,
		       langs[i].lines.comment,
		       langs[i].lines.code);
#endif
	}

	return 0;
}

int
main(int argc, char **argv)
{
        char *buf = NULL;     /* Buffer */
	size_t buf_s = 0;     /* Buffer size */
	char *ext = "";       /* File extension to be parsed */
	char *fext = "";      /* Discovered file extension */
	int fd;               /* File descriptor */
	int lmatch;           /* Matched language extension */
	int opt;              /* Command line option */

	setlocale(LC_CTYPE, "");

#ifdef __OpenBSD__
	if (pledge("rpath stdio", NULL) == -1)
		err(1, "pledge");
#endif

	while ((opt = getopt(argc, argv, "bcCt")) != -1) {
		switch (opt) {
		default:
			fprintf(stderr,
				"usage: %s [-bcCht] [files]\n",
				__progname);
			return 1;
		}
	}

	argv += optind;
	argc -= optind;

	if (argc > 0) {
		loc_init();

		do {
			if ((fd = open(*argv, O_RDONLY, 0)) == -1) {
				warn("%s", *argv);
				continue;
			}

			if (buf_s < MAXBSIZE &&
			    (buf = realloc(buf, MAXBSIZE)) == NULL)
				err(1, NULL);

			while((fext = strsep(argv, ".")) != NULL)
			        ext = fext;

			lmatch = loc_seek(ext);
			if (lmatch >= 0)
				loc_parse(lmatch, fd, buf);

		} while(*++argv);

		loc_results();
	}

	return 0;
}
