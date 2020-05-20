/* parse.c
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include "loc.h"

int
loc_parse(struct lang *l, int fd, char *buffer)
{
	char *character = NULL;
	char *previous  = NULL;
	ssize_t len     = 0;
	int in_comment  = 0;

	++l->counts.files;

	if ((len = read(fd, buffer, MAXBSIZE)) <= 0)
		return 0;

	for (character = buffer; len--; ++character) {
		switch (*character) {
		case '\n':
			if (*previous == '\n') {
				++l->counts.blank;
			} else if (in_comment) {
				++l->counts.comment;
			} else {
				++l->counts.code;
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
				++l->counts.comment;

			break;
		}

		previous = character;
	}

	return 0;
}
