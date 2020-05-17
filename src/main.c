/* loc.c - Summarize the lines of code within a file or directory
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include <string.h>

#include "loc.h"

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
		loc_langs_init();

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
