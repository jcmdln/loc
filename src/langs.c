/* langs.c
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include "loc.h"

// Add the definition of a language to the provided NULL pointer.
struct langs *
_lang_add(struct langs *node, char *name, char *ext,
	  char *comment, char *comment_open, char *comment_close)
{
	while (node != NULL && node->ext != ext && node->next != NULL)
		node = node->next;

	if (node->ext == ext)
		return node;

	node->next	     = malloc(sizeof(struct langs));
	node		     = node->next;

	node->name	     = malloc(sizeof(name));
	node->name	     = name;
	node->ext	     = malloc(sizeof(ext));
	node->ext	     = ext;
	node->comment.single = malloc(sizeof(comment));
	node->comment.single = comment;
	node->comment.open   = malloc(sizeof(comment_open));
	node->comment.open   = comment_open;
	node->comment.close  = malloc(sizeof(comment_close));
	node->comment.close  = comment_close;
	node->count.blank    = (uint32_t) malloc(sizeof(UINT32_MAX));
	node->count.blank    = 0;
	node->count.code     = (uint32_t) malloc(sizeof(UINT32_MAX));
	node->count.code     = 0;
	node->count.comment  = (uint32_t) malloc(sizeof(UINT32_MAX));
	node->count.comment  = 0;
	node->count.files    = (uint32_t) malloc(sizeof(UINT32_MAX));
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
