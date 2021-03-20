// results.c

#include "loc.h"

int _results_print(char *title, uint32_t files, uint32_t blank,
		   uint32_t comment, uint32_t code)
{
	printf("%-21s %11u %11u %11u %11u\n", title, files, blank, comment,
	       code);

	return 0;
}

int _results_separator(int width)
{
	int i;

	for (i = 0; i <= width; i++)
		printf("-");

	printf("\n");

	return 0;
}

int loc_results(struct langs *lang)
{
	struct langs *node = lang;
	struct counts total = { 0, 0, 0, 0 };

	printf("%-21s %11s %11s %11s %11s\n", "language", "files", "blank",
	       "comment", "code");

	_results_separator(68);

	while (node) {
		if (!node->name || !node->ext || node->count.files < 1) {
			node = node->next;
			continue;
		}

		_results_print(node->name, node->count.files, node->count.blank,
			       node->count.comment, node->count.code);

		total.files += node->count.files;
		total.blank += node->count.blank;
		total.comment += node->count.comment;
		total.code += node->count.code;

		node = node->next;
	}

	_results_separator(68);

	_results_print("Total", total.files, total.blank, total.comment,
		       total.code);

	return 0;
}
