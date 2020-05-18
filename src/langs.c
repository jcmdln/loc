/* langs.c
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include "loc.h"

struct lang langs[7];

int
_lang_init_c(int index)
{
	langs[index].name = "C";
	langs[index].ext = "c";
	langs[index].comments.single = "//";
	langs[index].comments.open = "/*";
	langs[index].comments.close = "*/";

	return 0;
}

int
_lang_init_c_header(int index) {
	langs[index].name = "C Header";
	langs[index].ext = "h";
	langs[index].comments.single = "//";
	langs[index].comments.open = "/*";
	langs[index].comments.close = "*/";

	return 0;
}

int
_lang_init_cpp(int index)
{
	langs[index].name = "C++";
	langs[index].ext = "cpp";
	langs[index].comments.single = "//";
	langs[index].comments.open = "/*";
	langs[index].comments.close = "*/";

	return 0;
}

int
_lang_init_cpp_header(int index)
{
	langs[index].name = "C++ Header";
	langs[index].ext = "hpp";
	langs[index].comments.single = "//";
	langs[index].comments.open = "/*";
	langs[index].comments.close = "*/";

	return 0;
}

int
_lang_init_makefile(int index)
{
	langs[index].name = "Makefile";
	langs[index].ext = "Makefile";
        langs[index].comments.single = "#";

	return 0;
}

int
_lang_init_meson(int index)
{
	langs[index].name = "Meson";
	langs[index].ext = "build";
        langs[index].comments.single = "#";

	return 0;
}

int
_lang_init_sh(int index)
{
	langs[index].name = "Shell Script";
	langs[index].ext = "sh";
        langs[index].comments.single = "#";

	return 0;
}

int
loc_langs_init(char *ext)
{
	uint32_t langs_s = sizeof(langs) / sizeof(langs[0]);
	uint32_t index = 0;

	for (index = 0; index < langs_s; index++) {
		if (langs[index].name == NULL)
		        break;

		if (strncasecmp(langs[index].ext, ext, 30) == 0)
		        return index;
	}

	if (ext == NULL)
		return -1;

	if (strncasecmp(ext, "c", 30) == 0) {
		_lang_init_c(index);
	} else if (strncasecmp(ext, "cpp", 30) == 0) {
		_lang_init_cpp(index);
	} else if (strncasecmp(ext, "h", 30) == 0) {
		_lang_init_c_header(index);
	} else if (strncasecmp(ext, "hpp", 30) == 0) {
		_lang_init_cpp_header(index);
	} else if (strncasecmp(ext, "Makefile", 30) == 0) {
		_lang_init_cpp_header(index);
	} else if (strncasecmp(ext, "build", 30) == 0) {
		_lang_init_meson(index);
	} else if (strncasecmp(ext, "sh", 30) == 0) {
		_lang_init_sh(index);
	} else {
		return -1;
	}

	return index;
}
