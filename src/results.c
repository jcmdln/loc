/* results.c
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include "loc.h"

int
_loc_results_print(char *title, uint32_t files, uint32_t blank,
		   uint32_t comment, uint32_t code)
{
	printf("%-25s  %10u  %10u  %10u	 %10u\n",
	       title, files, blank, comment, code);

	return 0;
}

int
_loc_results_separator(int width)
{
	for (int i = 0; i <= width; i++)
		printf("-");

	printf("\n");

	return 0;
}

int
loc_results(struct langs *lang)
{
	struct langs *this = lang;
	struct counts total = {0, 0, 0, 0};

	printf("%-25s  %10s  %10s  %10s	 %10s\n",
	       "language", "files", "blank", "comment", "code");

	_loc_results_separator(72);

	while (this != NULL) {
		if (this->name == NULL || this->ext == NULL  ||
		    this->count.files < 1) {
			this = this->next;
			continue;
		}

		_loc_results_print(this->name, this->count.files,
				   this->count.blank,
				   this->count.comment,
				   this->count.code);

		total.files   += this->count.files;
		total.blank   += this->count.blank;
		total.comment += this->count.comment;
		total.code    += this->count.code;

		this = this->next;
	}

	_loc_results_separator(72);

	_loc_results_print("Total", total.files, total.blank,
			   total.comment, total.code);

	return 0;
}
