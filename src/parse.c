/* parse.c
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include "loc.h"

int
loc_parse(struct langs *lang, int file, char *buffer)
{
	char *character = NULL;
	char *previous  = NULL;
	ssize_t len     = 0;
	int in_comment  = 0;

	++lang->count.files;

	len = read(file, buffer, MAXBSIZE);

	for (character = buffer; len--; ++character) {
		switch (*character) {
		case '\n':
			if (*previous == '\n') {
				++lang->count.blank;
			} else if (in_comment) {
				++lang->count.comment;
			} else {
				++lang->count.code;
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
				++lang->count.comment;

			break;
		}

		previous = character;
	}

	return 0;
}
