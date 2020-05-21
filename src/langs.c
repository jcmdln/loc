/* langs.c
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include "loc.h"

// _lang_add
struct langs *
_lang_add(struct langs *lang, char *name, char *ext, char *comment,
	  char *comment_open, char *comment_close)
{
	struct langs *this = lang;

	while (this->next != NULL && this->ext != ext)
		this = this->next;

	if (this->ext == ext) {
		return this;
	}

	this->next = malloc(sizeof(struct langs));
	this	   = this->next;
	this->name = name;
	this->ext  = ext;

	this->comment.single = comment;
	this->comment.open   = comment_open;
	this->comment.close  = comment_close;

	this->count.blank    = 0;
	this->count.code     = 0;
	this->count.comment  = 0;
	this->count.files    = 0;

	return this;
}

// loc_langs_init
struct langs *
loc_langs_init(struct langs *lang, char *ext)
{
	struct langs *this = NULL;

	if (strncasecmp(ext, "c", 30) == 0) {

		this = _lang_add(lang, "C", "c",
				 "//", "/*", "*/");

	} else if (strncasecmp(ext, "h", 30) == 0) {

		this = _lang_add(lang, "C/C++ Header", "h",
				 "//", "/*", "*/");

	} else if (strncasecmp(ext, "cpp", 30) == 0) {

		this = _lang_add(lang, "C++", "cpp",
				 "//", "/*", "*/");

	} else if (strncasecmp(ext, "hpp", 30) == 0) {

		this = _lang_add(lang, "C++ Header", "hpp",
				 "//", "/*", "*/");

	} else if (strncasecmp(ext, "Makefile", 30) == 0) {

		this = _lang_add(lang, "Makefile", "Makefile",
				 "#", NULL, NULL);

	} else if (strncasecmp(ext, "md", 30) == 0) {
		/*
		 * TODO: Markdown comment parsing is weird, and will
		 * require a full parser rewrite.
		 */
		this = _lang_add(lang, "Markdown", "md",
				 NULL, NULL, NULL);

	} else if (strncasecmp(ext, "sh", 30) == 0) {

		this = _lang_add(lang, "Shell Script", "sh",
				 "#", NULL, NULL);
	}

	return this;
}
