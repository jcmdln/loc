/* loc.h */

#include <sys/param.h>
#include <sys/stat.h>

#include <err.h>
#include <fcntl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


char *__progname;


struct loc {
	uint64_t blank;
	uint64_t code;
	uint64_t comment;
	uint64_t total;
};

struct lang {
	char *name;
	char *ext;
	char *comment_single;
	char *comment_multi_start;
	char *comment_multi_end;
	uint64_t files;
	struct loc lines;
};

struct lang langs[2];

int
loc_init();

int
loc_parse(int i, int fd, char *buf);

int
loc_seek(char *ext);
