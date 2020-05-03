/* parse.c */

#include <strings.h>

#include "loc.h"

int
loc_seek(char *ext)
{
	int langs_s = sizeof(langs);

	for (int i = 0; i < langs_s; i++) {
		if (strncasecmp(langs[i].ext, ext, 20) == 0) {
			return i;
		}
	}

	return -1;
}


int
loc_parse(int i, int fd, char *buffer)
{
	char *character, *previous = "";
	uint8_t in_comment = 0;
	ssize_t len;

	if ((len = read(fd, buffer, MAXBSIZE)) > 0) {
		++langs[i].files;

		for (character = buffer; len--; ++character) {
			switch (*character) {
			case '\n':
				if (in_comment) {
					++langs[i].lines.comment;
				} else if (*previous == '\n') {
					++langs[i].lines.blank;
				}

				++langs[i].lines.total;
				break;
			case '*':
				if (*previous == '/')
					in_comment = 1;
			case '/':
				if (in_comment && *previous == '*') {
					in_comment = 0;
					++langs[i].lines.comment;
				} else if (*previous == '/') {
					++langs[i].lines.comment;
				}
			}

			previous = character;
		}

		langs[i].lines.code = langs[i].lines.total
			- langs[i].lines.blank
			- langs[i].lines.comment;
	}

	return 0;
}
