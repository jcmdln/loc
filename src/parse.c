// parse.c

#include "loc.h"

int loc_parse(struct langs *lang, int file, char *buffer)
{
	char *character = NULL;
	char *previous = NULL;
	ssize_t len = 0;
	int in_comment = 0;

	++lang->count.files;

	while ((len = read(file, buffer, MAXBSIZE)) > 0) {
		for (character = buffer; len--; ++character) {
			switch (*character) {
			case '\n':
				if (previous != NULL && *previous == '\n') {
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
	}

	return 0;
}
