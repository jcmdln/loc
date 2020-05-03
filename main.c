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

		printf("%-24s  %10llu  %10llu  %10llu  %10llu\n",
		       langs[i].name,
		       langs[i].files,
		       langs[i].lines.blank,
		       langs[i].lines.comment,
		       langs[i].lines.code);
	}

	return 0;
}


int
main(int argc, char **argv)
{
	static char *buffer;
	static size_t buffer_size;
	char *extension, *file_extension;
	int fd, l, opt;

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
		loc_init();

		do {
			if ((fd = open(*argv, O_RDONLY, 0)) == -1){
				warn("%s", *argv);
				continue;
			}

			if (buffer_size < MAXBSIZE &&
			    (buffer = realloc(buffer, MAXBSIZE)) == NULL)
				err(1, NULL);

			while((file_extension = strsep(argv, ".")) != NULL)
			        extension = file_extension;

			l = loc_seek(extension);
			if (l >= 0)
				loc_parse(l, fd, buffer);
		} while(*++argv);

		loc_results();
	}

	return 0;
}
