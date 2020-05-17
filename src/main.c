/* loc.c - Summarize the lines of code within a file or directory
 *
 * Copyright 2020 Johnathan C. Maudlin <jcmdln@gmail.com>
 */

#include <inttypes.h>
#include <stdint.h>
#include <string.h>

#include "loc.h"

uint32_t opt_blank;
uint32_t opt_code;
uint32_t opt_comment;

int
_loc_results_separator(int width)
{
	for (int i = 0; i <= width; i++)
		printf("-");

	printf("\n");
	return 0;
}

int
_loc_results_print(char *title, uint64_t files, uint64_t blank,
		   uint64_t comment, uint64_t code)
{
	printf("%-24s  %10" PRIu64 "  %10" PRIu64 "  %10" PRIu64
	       "  %10" PRIu64 "\n",
	       title, files, blank, comment, code);

	return 0;
}

int
loc_results()
{
	struct lang total;
	total.files = 0;
	total.lines.blank = 0;
	total.lines.comment = 0;
	total.lines.code = 0;

	printf("%-24s  %10s  %10s  %10s  %10s\n",
	       "language", "files", "blank", "comment", "code");

	_loc_results_separator(72);

	for (int i = 0; i <= 1; i++) {
		if (langs[i].files < 1 || langs[i].name == NULL)
			continue;

		_loc_results_print(langs[i].name, langs[i].files,
		       langs[i].lines.blank, langs[i].lines.comment,
		       langs[i].lines.code);

	        total.files += langs[i].files;
		total.lines.blank += langs[i].lines.blank;
		total.lines.comment += langs[i].lines.comment;
		total.lines.code += langs[i].lines.code;
	}

	_loc_results_separator(72);

	_loc_results_print("total", total.files, total.lines.blank,
	       total.lines.comment, total.lines.code);

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
