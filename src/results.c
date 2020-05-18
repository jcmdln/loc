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

	struct lang total;
	total.name = "Total";
	total.counts.files = 0;
	total.counts.blank = 0;
	total.counts.comment = 0;
	total.counts.code = 0;

	printf("%-24s  %10s  %10s  %10s  %10s\n",
	       "language", "files", "blank", "comment", "code");

	_loc_results_separator(72);

	for (uint32_t i = 0; i < langs_s; i++) {
		if (langs[i].name == NULL || langs[i].ext == NULL)
		        continue;

		if (langs[i].counts.files < 1)
			continue;

		_loc_results_print(langs[i].name, langs[i].counts.files,
		       langs[i].counts.blank, langs[i].counts.comment,
		       langs[i].counts.code);

	        total.counts.files   += langs[i].counts.files;
		total.counts.blank   += langs[i].counts.blank;
		total.counts.comment += langs[i].counts.comment;
		total.counts.code    += langs[i].counts.code;
	}

	_loc_results_separator(72);

	_loc_results_print(total.name, total.counts.files, total.counts.blank,
	       total.counts.comment, total.counts.code);

	return 0;
}
