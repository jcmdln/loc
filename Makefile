# Makefile

PROG=	loc
SRCS=	loc.h langs.c main.c parse.c

ifeq ($(uname), OpenBSD)
.include <bsd.prog.mk>
else
PREFIX=		/usr/local
BINDIR=		$(PREFIX)/bin
LIBDIR=		$(PREFIX)/lib
INCLUDEDIR=	$(PREFIX)/include
MANDIR=		$(PREFIX)/man

CC=		cc
CFLAGS=		-O2 -pipe -g -Wall -pedantic
LDFLAGS=	$(shell pkg-config --cflags libbsd-overlay)
LDLIBS=		$(shell pkg-config --libs libbsd-overlay)

all: $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(PROG) $(SRCS)
endif
