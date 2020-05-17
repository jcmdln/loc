/* langs.c
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include "loc.h"

struct lang langs[7];

int
loc_langs_init()
{
	langs[0].name = "C";
	langs[0].ext = "c";
	langs[0].comment_single = "//";
	langs[0].comment_multi_start = "/*";
	langs[0].comment_multi_end = "*/";

	langs[1].name = "C/C++ Header";
	langs[1].ext = "h";
	langs[1].comment_single = "//";
	langs[1].comment_multi_start = "/*";
	langs[1].comment_multi_end = "*/";

	langs[2].name = "Makefile";
	langs[2].ext = "Makefile";
        langs[2].comment_single = "#";

	langs[3].name = "Meson";
	langs[3].ext = "build";
        langs[3].comment_single = "#";

	langs[4].name = "Shell Script";
	langs[4].ext = "sh";
        langs[4].comment_single = "#";

	langs[5].name = "C++ Header";
	langs[5].ext = "hpp";
	langs[5].comment_single = "//";
	langs[5].comment_multi_start = "/*";
	langs[5].comment_multi_end = "*/";

	langs[6].name = "C++";
	langs[6].ext = "cpp";
	langs[6].comment_single = "//";
	langs[6].comment_multi_start = "/*";
	langs[6].comment_multi_end = "*/";

	return 0;
}
