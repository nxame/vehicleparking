CC ?= cc
CFLAGS ?= -O2 -Wall
TARGET = parking

UNAME_S := $(shell uname -s 2>/dev/null)

ifeq ($(UNAME_S),Darwin)
CURSES_LIBS = -lncurses
else ifeq ($(UNAME_S),Linux)
CURSES_LIBS = -lncursesw
else
MINGW_PREFIX ?= /mingw64
CURSES_CFLAGS = -I$(MINGW_PREFIX)/include/pdcurses -DPDC_WIDE -DPDC_FORCE_UTF8
CURSES_LIBS = -lpdcurses_wincon -lwinmm
endif

SRCS = PARKING.C conio_compat.c datapath.c

$(TARGET): $(SRCS) conio_compat.h datapath.h
	$(CC) $(CFLAGS) $(CURSES_CFLAGS) -x c -o $(TARGET) $(SRCS) $(CURSES_LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
