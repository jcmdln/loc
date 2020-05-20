/* langs.c
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include "loc.h"

// _lang_add
struct lang *
_lang_add(struct lang *l, char *name, char *ext, char *comment,
	  char *comment_open, char *comment_close)
{
	struct lang *this = l;

	while (this->next != NULL && this->ext != ext)
		this = this->next;

	if (this->ext == ext) {
		return this;
	}

        this->next = malloc(sizeof(struct lang));
	this       = this->next;
        this->name = name;
        this->ext  = ext;

        this->comments.single = comment;
	this->comments.open   = comment_open;
	this->comments.close  = comment_close;

	this->counts.blank    = 0;
	this->counts.code     = 0;
	this->counts.comment  = 0;
	this->counts.files    = 0;

        return this;
}

// loc_langs_init
struct lang *
loc_langs_init(struct lang *l, char *ext)
{
	struct lang *this = NULL;

	if (strncasecmp(ext, "c", 30) == 0) {
		this = _lang_add(l, "C", "c", "//", "/*", "*/");
	} else if (strncasecmp(ext, "h", 30) == 0) {
		this = _lang_add(l, "C/C++ Header", "h", "//", "/*", "*/");
	} else if (strncasecmp(ext, "cpp", 30) == 0) {
		this = _lang_add(l, "C++", "cpp", "//", "/*", "*/");
	} else if (strncasecmp(ext, "hpp", 30) == 0) {
		this = _lang_add(l, "C++ Header", "hpp", "//", "/*", "*/");
	} else if (strncasecmp(ext, "sh", 30) == 0) {
		this = _lang_add(l, "Shell Script", "sh", "#", NULL, NULL);
	} else if (strncasecmp(ext, "Makefile", 30) == 0) {
		this = _lang_add(l, "Makefile", "Makefile", "#", NULL, NULL);
	}

	return this;
}
