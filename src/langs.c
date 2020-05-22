/* langs.c
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include "loc.h"

// Add the definition of a language to the provided NULL pointer.
struct langs *
_lang_add(struct langs *lang, char *name, char *ext,
	  char *comment, char *comment_open, char *comment_close)
{
	struct langs *node = lang;

	while (node->next != NULL && node->ext != ext)
		node = node->next;

	if (node->ext == ext)
		return node;

	node->next = malloc(sizeof(struct langs));
	node       = node->next;
	node->name = name;
	node->ext  = ext;

	node->comment.single = comment;
	node->comment.open   = comment_open;
	node->comment.close  = comment_close;

	node->count.blank    = 0;
	node->count.code     = 0;
	node->count.comment  = 0;
	node->count.files    = 0;

	return node;
}

// loc_langs_init
struct langs *
loc_langs_init(struct langs *lang, char *ext)
{
	struct langs *node = NULL;

	if (strncasecmp(ext, "c", 30) == 0) {
		node = _lang_add(lang, "C", "c", "//", "/*", "*/");
	} else if (strncasecmp(ext, "h", 30) == 0) {
	        node = _lang_add(lang, "C/C++ Header", "h", "//", "/*", "*/");
	} else if (strncasecmp(ext, "cpp", 30) == 0) {
		node = _lang_add(lang, "C++", "cpp", "//", "/*", "*/");
	} else if (strncasecmp(ext, "hpp", 30) == 0) {
	        node = _lang_add(lang, "C++ Header", "hpp", "//", "/*", "*/");
	} else if (strncasecmp(ext, "Makefile", 30) == 0) {
		node = _lang_add(lang, "Makefile", "Makefile", "#", NULL, NULL);
	} else if (strncasecmp(ext, "md", 30) == 0) {
		node = _lang_add(lang, "Markdown", "md", NULL, NULL, NULL);
	} else if (strncasecmp(ext, "sh", 30) == 0) {
	        node = _lang_add(lang, "Shell Script", "sh", "#", NULL, NULL);
	}

	return node;
}
