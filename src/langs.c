/* langs.c
 *
 * Copyright 2020 Johnathan C. Maudlin
 */

#include "loc.h"
#include <stdint.h>

struct langs *
_lang_add(struct langs *node, char *name, char *ext,
	  char *comment, char *comment_open, char *comment_close)
{
	if (!node)
		node = malloc(sizeof(struct langs));

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

	node->count.blank    = 0;
	node->count.code     = 0;
	node->count.comment  = 0;
	node->count.files    = 0;

	return node;
}

struct langs *
_lang_find(struct langs *lang, char *ext)
{
	struct langs *node = lang;

	while (node && node->next && strncasecmp(ext, node->ext, 30) != 0)
		node = node->next;

	if (node && node->ext && strncasecmp(ext, node->ext, 30) != 0) {
		node->next = (struct langs *) malloc(sizeof(struct langs));
		node = node->next;
	}

	return node;
}

struct langs *
loc_langs_init(struct langs *lang, char *ext)
{
	struct langs *node = NULL;

	if ((node = _lang_find(lang, ext)) && node->ext)
		return node;

	if (strncasecmp(ext, "c", 30) == 0)
		_lang_add(node, "C", "c", "//", "/*", "*/");
	else if (strncasecmp(ext, "h", 30) == 0)
		_lang_add(node, "C/C++ Header", "h", "//", "/*", "*/");
	else if (strncasecmp(ext, "cpp", 30) == 0)
		_lang_add(node, "C++", "cpp", "//", "/*", "*/");
	else if (strncasecmp(ext, "hpp", 30) == 0)
		_lang_add(node, "C++ Header", "hpp", "//", "/*", "*/");
	else if (strncasecmp(ext, "Makefile", 30) == 0)
		_lang_add(node, "Makefile", "Makefile", "#", NULL, NULL);
	else if (strncasecmp(ext, "md", 30) == 0)
		_lang_add(node, "Markdown", "md", NULL, NULL, NULL);
	else if (strncasecmp(ext, "sh", 30) == 0)
		_lang_add(node, "Shell Script", "sh", "#", NULL, NULL);

	return node;
}
