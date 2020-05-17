/* results.c
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include "loc.h"

int
_loc_results_separator(int width)
{
	for (int i = 0; i <= width; i++)
		printf("-");

	printf("\n");
	return 0;
}

int
_loc_results_print(char *title, uint32_t files, uint32_t blank,
		   uint32_t comment, uint32_t code)
{
	printf("%-24s  %10u  %10u  %10u  %10u\n",
	       title, files, blank, comment, code);

	return 0;
}

int
loc_results()
{
	uint32_t langs_s = sizeof(langs) / sizeof(langs[0]);
	uint32_t i;

	struct lang total;
	total.name = "Total";
	total.files = 0;
	total.lines.blank = 0;
	total.lines.comment = 0;
	total.lines.code = 0;

	printf("%-24s  %10s  %10s  %10s  %10s\n",
	       "language", "files", "blank", "comment", "code");

	_loc_results_separator(72);

	for (i = 0; i < langs_s; i++) {
		if (langs[i].name == NULL || langs[i].ext == NULL)
		        continue;

		if (langs[i].files < 1)
			continue;

		_loc_results_print(langs[i].name, langs[i].files,
		       langs[i].lines.blank, langs[i].lines.comment,
		       langs[i].lines.code);

	        total.files += langs[i].files;
		total.lines.blank += langs[i].lines.blank;
		total.lines.comment += langs[i].lines.comment;
		total.lines.code += langs[i].lines.code;
	}

	_loc_results_separator(72);

	_loc_results_print(total.name, total.files, total.lines.blank,
	       total.lines.comment, total.lines.code);

	return 0;
}
