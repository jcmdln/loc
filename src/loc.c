// loc.c

#include "loc.h"

struct comments {
	char *single;
	char *open;
	char *close;
};

struct counts {
	uint32_t blank;
	uint32_t code;
	uint32_t comment;
	uint32_t files;
};

struct langs {
	char *		name;
	char *		ext;
	struct comments comment;
	struct counts	count;
	struct langs *	next;
};

void	      lang_add(struct langs *, char *, char *, char *, char *, char *);
struct langs *lang_find(struct langs *, char *);
void	      lang_parse(struct langs *, int, char *);
void	      loc_results(struct langs *);
void	      _safe_add_u32_to_p(uint32_t, uint32_t *);
void	      _safe_inc_u32(uint32_t *);
void	      _results_print(char *, uint32_t, uint32_t, uint32_t, uint32_t);
void	      _results_separator(int);

int
main(int argc, char **argv)
{
	struct langs *lang = NULL;
	struct langs *node = NULL;

	char * buf = NULL;
	size_t buf_s = 0;
	char * ext = NULL;
	char * ext_f = NULL;
	int    fd = 0;
	int    opt = 0;

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

	lang = malloc(sizeof(struct langs));
	lang->name = NULL;
	lang->ext = NULL;
	lang->next = NULL;

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
		struct langs *l, *h = NULL;
		for (l = lang; l != NULL; l = h) {
			h = l->next;
			free(l);
		}
	}

	return EXIT_SUCCESS;
}

void
lang_add(struct langs *lang, char *name, char *ext, char *comment,
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

struct langs *
lang_find(struct langs *lang, char *ext)
{
	while (lang->ext) {
		if (strncasecmp(ext, lang->ext, MAXBSIZE) == 0)
			return lang;

		if (!lang->next) {
			lang->next = malloc(sizeof(struct langs));
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
lang_parse(struct langs *lang, int fd, char *buf)
{
	ssize_t buf_l = 0;
	size_t	buf_s = MAXBSIZE;
	char *	char_cur = NULL;
	char *	char_prev = NULL;
	// bool	in_comment = false;
	// bool	in_newline = true;

	_safe_inc_u32(&lang->count.files);

	while ((buf_l = read(fd, buf, buf_s)) > 0) {
		for (char_cur = buf; buf_l--; ++char_cur) {
			char_prev = char_cur;
		}
	}
}

void
loc_results(struct langs *lang)
{
	struct counts total = {0, 0, 0, 0};

	printf("%-21s %11s %11s %11s %11s\n", "language", "files", "blank",
	    "comment", "code");

	_results_separator(68);

	while (lang) {
		_results_print(lang->name, lang->count.files, lang->count.blank,
		    lang->count.comment, lang->count.code);

		_safe_add_u32_to_p(lang->count.files, &total.files);
		_safe_add_u32_to_p(lang->count.blank, &total.blank);
		_safe_add_u32_to_p(lang->count.comment, &total.comment);
		_safe_add_u32_to_p(lang->count.code, &total.code);

		lang = lang->next;
	}

	_results_separator(68);

	_results_print("Total", total.files, total.blank, total.comment,
	    total.code);
}

void
_results_print(char *title, uint32_t files, uint32_t lines_blank,
    uint32_t lines_comment, uint32_t lines_code)
{
	printf("%-21s %11u %11u %11u %11u\n", title, files, lines_blank,
	    lines_comment, lines_code);
}

void
_results_separator(int width)
{
	for (int i = 0; i <= width; i++)
		printf("-");

	printf("\n");
}

void
_safe_add_u32_to_p(uint32_t a, uint32_t *b)
{
	if (*b > UINT32_MAX - a)
		err(1, NULL);
	else
		*b += a;
}

void
_safe_inc_u32(uint32_t *counter)
{
	if (*counter > UINT32_MAX - 1)
		err(1, NULL);
	else
		++*counter;
}
