/* parse.c
 *
 * Copyright 2020 Johnathan C. Maudlin
 */


#include <ctype.h>
#include <strings.h>

#include "loc.h"

int
loc_seek(char *ext)
{
	uint32_t langs_s = sizeof(langs) / sizeof(langs[0]);
	uint32_t i;

	for (i = 0; i < langs_s; i++) {
		if (langs[i].name == NULL || langs[i].ext == NULL)
		        break;

		if (strncasecmp(langs[i].ext, ext, 30) == 0)
			return i;
	}

        return -1;
}

int
loc_parse(int i, int fd, char *buffer)
{
	char *character = NULL;
	char *previous = NULL;
	ssize_t len;
	int in_comment = 0;

	++langs[i].files;

	if ((len = read(fd, buffer, MAXBSIZE)) <= 0)
		return 0;

	for (character = buffer; len--; ++character) {
		switch (*character) {
		case '\n':
			if (*previous == '\n') {
				++langs[i].lines.blank;
			} else if (in_comment) {
				++langs[i].lines.comment;
			} else {
				++langs[i].lines.code;
			}

			break;

		case '*':
			if (!in_comment && *previous == '/')
				in_comment = 1;

			break;

		case '/':
			if (previous == NULL)
				break;

			if (in_comment && *previous == '*')
				in_comment = 0;

			if (*previous == '*' || *previous == '/')
				++langs[i].lines.comment;

			break;
		}

		previous = character;
	}

	return 0;
}
