// loc.c

#include "loc.h"

typedef struct loc_comments {
	char *single;
	char *open;
	char *close;
} loc_comments;

typedef struct loc_counts {
	uint32_t blank;
	uint32_t code;
	uint32_t comment;
	uint32_t files;
} loc_counts;

typedef struct loc_langs {
	char *name;
	char *ext;
	loc_comments comment;
	loc_counts count;
	struct loc_langs *next;
} loc_langs;

void lang_add(loc_langs *, char *, char *, char *, char *, char *);
loc_langs *lang_find(loc_langs *, char *);
void lang_parse(loc_langs *, int, char *);
void loc_results(loc_langs *);
void _add_u32_to_p(uint32_t, uint32_t *);
void _inc_u32_p(uint32_t *);
void _results_print(char *, uint32_t, uint32_t, uint32_t, uint32_t);
void _results_separator(int);

int
main(int argc, char **argv)
{
	loc_langs *lang = NULL;
	loc_langs *node = NULL;

	char *buf = NULL;
	size_t buf_s = 0;
	char *ext = NULL;
	char *ext_f = NULL;
	int fd = 0;
	int opt = 0;

#ifdef __OpenBSD__
	if (pledge("rpath stdio", NULL) == -1)
		err(1, "pledge");
#endif

	while ((opt = getopt(argc, argv, "h")) != -1)
		switch (opt) {
		default:
			fprintf(stderr, "usage: %s [-h] files...\n",
			    __progname);
			return EXIT_FAILURE;
		}

	argc -= optind;
	argv += optind;

	if (argc < 1) {
		fprintf(stderr, "%s: missing operand(s)\n", __progname);
		return EXIT_FAILURE;
	}

	lang = malloc(sizeof(loc_langs));
	lang_add(lang, NULL, NULL, NULL, NULL, NULL);

	do {
		if ((fd = open(*argv, O_RDONLY, 0)) == -1) {
			warn("%s", *argv);
			continue;
		}

		if (buf_s < MAXBSIZE && (buf = realloc(buf, MAXBSIZE)) == NULL)
			err(1, NULL);

		while ((ext_f = strsep(argv, ".")))
			ext = ext_f;

		if ((node = lang_find(lang, ext)))
			lang_parse(node, fd, buf);

		if (close(fd) != 0)
			err(1, NULL);
	} while (*++argv);

	if (lang && lang->name)
		loc_results(lang);

	if (buf)
		free(buf);

	if (lang) {
		loc_langs *l, *h = NULL;
		for (l = lang; l != NULL; l = h) {
			h = l->next;
			free(l);
		}
	}

	return EXIT_SUCCESS;
}

void
lang_add(loc_langs *lang, char *name, char *ext, char *comment,
    char *comment_open, char *comment_close)
{
	lang->name = name;
	lang->ext = ext;
	lang->comment.close = comment_close;
	lang->comment.open = comment_open;
	lang->comment.single = comment;
	lang->count.blank = 0;
	lang->count.code = 0;
	lang->count.comment = 0;
	lang->count.files = 0;
	lang->next = NULL;
}

loc_langs *
lang_find(loc_langs *lang, char *ext)
{
	while (lang->ext) {
		if (strncasecmp(ext, lang->ext, MAXBSIZE) == 0)
			return lang;

		if (!lang->next) {
			lang->next = malloc(sizeof(loc_langs));
			lang = lang->next;
			break;
		}

		lang = lang->next;
	}

	if (strncasecmp(ext, "c", MAXBSIZE) == 0)
		lang_add(lang, "C", "c", "//", "/*", "*/");
	else if (strncasecmp(ext, "h", MAXBSIZE) == 0)
		lang_add(lang, "C/C++ Header", "h", "//", "/*", "*/");
	else if (strncasecmp(ext, "Makefile", MAXBSIZE) == 0)
		lang_add(lang, "Makefile", "Makefile", "#", NULL, NULL);
	else if (strncasecmp(ext, "md", MAXBSIZE) == 0)
		lang_add(lang, "Markdown", "md", NULL, NULL, NULL);
	else if (strncasecmp(ext, "sh", MAXBSIZE) == 0)
		lang_add(lang, "Shell Script", "sh", "#", NULL, NULL);

	return lang;
}

void
lang_parse(loc_langs *lang, int fd, char *buf)
{
	ssize_t buf_s = 0;
	char *char_cur = NULL;
	char *char_prev = NULL;

	_inc_u32_p(&lang->count.files);

	while ((buf_s = read(fd, buf, MAXBSIZE)) > 0)
		for (char_cur = buf; buf_s--; ++char_cur) {
			switch (*char_cur) {
			case '\n':
				if (*char_prev == '\n')
					_inc_u32_p(&lang->count.blank);
				else
					_inc_u32_p(&lang->count.code);
				break;
			}

			char_prev = char_cur;
		}
}

void
loc_results(loc_langs *lang)
{
	loc_counts total = {0, 0, 0, 0};

	printf("%-21s %11s %11s %11s %11s\n", "language", "files", "blank",
	    "comment", "code");

	_results_separator(68);

	while (lang) {
		_results_print(lang->name, lang->count.files, lang->count.blank,
		    lang->count.comment, lang->count.code);

		_add_u32_to_p(lang->count.files, &total.files);
		_add_u32_to_p(lang->count.blank, &total.blank);
		_add_u32_to_p(lang->count.comment, &total.comment);
		_add_u32_to_p(lang->count.code, &total.code);

		lang = lang->next;
	}

	_results_separator(68);

	_results_print("Total", total.files, total.blank, total.comment,
	    total.code);
}

void
_add_u32_to_p(uint32_t a, uint32_t *b)
{
	if (*b > UINT32_MAX - a)
		err(1, NULL);
	else
		*b += a;
}

void
_inc_u32_p(uint32_t *counter)
{
	if (*counter > UINT32_MAX - 1)
		err(1, NULL);
	else
		++*counter;
}

void
_results_print(char *title, uint32_t files, uint32_t blank, uint32_t comment,
    uint32_t code)
{
	printf("%-21s %11u %11u %11u %11u\n", title, files, blank, comment,
	    code);
}

void
_results_separator(int width)
{
	for (int i = 0; i <= width; i++)
		printf("-");

	printf("\n");
}
