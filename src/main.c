// loc.c

#include "loc.h"

int loc(char **argv)
{
	struct langs *lang = malloc(sizeof(struct langs));
	struct langs *node = malloc(sizeof(struct langs));

	char *buf = NULL; // Buffer
	size_t buf_s = 0; // Buffer size
	char *ext = "";	  // File extension to be parsed
	char *fext = "";  // Discovered file extension
	int fd = 0;	  // File descriptor

	do {
		if ((fd = open(*argv, O_RDONLY, 0)) == -1) {
			warn("%s", *argv);
			continue;
		}

		if (buf_s < MAXBSIZE && (buf = realloc(buf, MAXBSIZE)) == NULL)
			err(1, NULL);

		while ((fext = strsep(argv, ".")) != NULL)
			ext = fext;

		if ((node = loc_langs_init(lang, ext)) != NULL)
			loc_parse(node, fd, buf);

		if (close(fd) != 0)
			err(1, NULL);

	} while (*++argv);

	loc_results(lang);

	free(lang);

	return 0;
}

int main(int argc, char **argv)
{
	setlocale(LC_CTYPE, "");

	int opt = 0;

#ifdef __OpenBSD__
	if (pledge("rpath stdio", NULL) == -1)
		err(1, "pledge");
#endif

	while ((opt = getopt(argc, argv, "bcCt")) != -1)
		switch (opt) {
		default:
			fprintf(stderr, "usage: %s [-bcCht] [files]\n",
				__progname);
			return 1;
		}

	argv += optind;
	argc -= optind;

	if (argc < 1)
		return 0;

	loc(argv);

	return 0;
}
