/* parse.c */

#include <strings.h>

#include "loc.h"

int
loc_seek(char *ext)
{
	int64_t langs_s = sizeof(langs);

	for (int i = 0; i < langs_s; i++) {
		if (strncasecmp(langs[i].ext, ext, 20) == 0)
			return i;
	}

	return -1;
}

int
loc_parse(int i, int fd, char *buffer)
{
	char *character = NULL;
	char *previous = NULL;
	ssize_t len = 0;
	int in_comment = 0;

	if ((len = read(fd, buffer, MAXBSIZE)) <= 0) {
		/* No need to scan or count an empty file */
		return 0;
	}

	++langs[i].files;

	for (character = buffer; len--; ++character) {
		switch (*character) {
		case '\n':
			if (in_comment)
				++langs[i].lines.comment;

			if (*previous == '\n') {
				++langs[i].lines.blank;
			} else if (!in_comment)
				++langs[i].lines.code;

			++langs[i].lines.total;

			break;

		case '*':
			if (*previous == '/')
				in_comment = 1;

			break;

		case '/':
			if (in_comment && *previous == '*') {
				in_comment = 0;
				++langs[i].lines.comment;
			}

			if (in_comment != 0 && *previous == '/')
				++langs[i].lines.comment;

			break;
		}

		previous = character;
	}

	return 0;
}
