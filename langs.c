/* langs.c */

#include "loc.h"

int
loc_init()
{
	langs[0].name = "C";
	langs[0].ext = "c";
	langs[0].comment_single = "//";
	langs[0].comment_multi_start = "/*";
	langs[0].comment_multi_end = "*/";

	langs[1].name = "C Header";
	langs[1].ext = "h";
	langs[1].comment_single = "//";
	langs[1].comment_multi_start = "/*";
	langs[1].comment_multi_end = "*/";

	return 0;
}
