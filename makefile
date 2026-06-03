.POSIX:
.DELETE_ON_ERROR:

USE_WIRINGPI ?= 0
USE_GPIO ?= 0
USE_FLTO ?= 0

CC   := gcc
LIBS := -lm -ldl -pthread
INCS :=
CFLAGS := $(INCS) -Wall -O3 
DESTDIR :=
PREFIX  := /usr/local
BINDIR  := /bin
DEST    := $(DESTDIR)$(PREFIX)$(BINDIR)

CURSES_CFLAGS := $(shell command -v ncursesw6-config >/dev/null 2>&1 && ncursesw6-config --cflags || echo "")
CURSES_LIBS   := $(shell command -v ncursesw6-config >/dev/null 2>&1 && ncursesw6-config --libs || echo "-lncurses")


NPROLOG ?= $(CURDIR)
export NPROLOG

SHAREDIR ?= $(PREFIX)/share/mprolog
export SHAREDIR

MPL   := mpl
EDLOG := edlog


ifeq ($(shell uname -n),raspberrypi)
CFLAGS += -D__rpi__
endif

ifeq ($(shell uname -n),raspberrypi)
ifeq ($(USE_WIRINGPI),1)
CFLAGS += -D__rpiwiring__
LIBS += -lwiringPi
endif
endif


ifeq  ($(shell uname -n),raspberrypi)
ifeq ($(USE_GPIO),1)
CFLAGS += -D__rpigpio__
LIBS += -lgpiod
endif
endif


ifeq ($(USE_FLTO),1)
CFLAGS += -flto
endif
ifeq ($(USE_GDB),1)
CFLAGS += -O0 -g
endif

MPL_OBJS := main.o \
	parser.o \
	function.o \
	builtin.o \
	extension.o \
	parallel.o \
	superset.o \
	link.o \
	data.o \
	gbc.o \
	cell.o \
	error.o \
	bignum.o \
	compute.o \
	clp.o \
	edit.o \
	syntax_highlight.o


EDLOG_OBJS := edlog.o syntax_highlight.o


SRC_PROLOG := library/opengl.pl \
	library/plot.pl \
	library/python.pl \
	library/tcltk.pl

OBJ_PROLOG := $(SRC_PROLOG:.pl=.o)


./library/%.o: ./library/%.pl $(MPL)
	echo "use_module(compiler),compile_file('./$<')." | ./$(MPL) -r
	touch $@

TARGETS := $(MPL) $(EDLOG)

all: $(TARGETS)


$(MPL): $(MPL_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)


$(EDLOG): $(EDLOG_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CURSES_LIBS)

edlog.o: edlog.c edlog.h term.h
	$(CC) $(CFLAGS) -c $< $(CURSES_CFLAGS)


%.o: %.c mpl.h
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: install
install: $(MPL) $(EDLOG)
	mkdir -p $(DEST)
	install -s $(MPL) $(DEST)
	install -s $(EDLOG) $(DEST)
	mkdir -p $(DESTDIR)$(SHAREDIR)
	install -m 644 library/* $(DESTDIR)$(SHAREDIR)


.PHONY: prolog
prolog: $(OBJ_PROLOG)

.PHONY: uninstall
uninstall:
	rm -f $(DEST)/$(MPL) $(DEST)/$(EDLOG)

# clean
.PHONY: clean all
clean:
	rm -f *.o $(MPL) $(EDLOG) $(OBJ_PROLOG)


.PHONY: check
check:
	cppcheck --enable=warning,performance,portability --std=c17 --library=posix -j4 .
