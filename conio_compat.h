/*
 * conio_compat.h
 * Borland/Turbo C DOS console API (<conio.h> + <dos.h>) implemented on top
 * of curses, so the original 2011 PARKING.C builds unchanged (almost) on
 * macOS, Linux (ncurses) and Windows (PDCurses).
 */
#ifndef CONIO_COMPAT_H
#define CONIO_COMPAT_H

#include <stdio.h>

/* Borland text color constants (conio.h) */
enum {
	BLACK = 0, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
	DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA,
	YELLOW, WHITE
};

/* Borland cursor types (conio.h) */
#define _NOCURSOR    0
#define _NORMALCURSOR 1
#define _SOLIDCURSOR 2

/* Borland date/time structs (dos.h) */
struct date {
	int da_year;
	int da_day;
	int da_mon;
};

struct time {
	int ti_hour;
	int ti_min;
	int ti_sec;
	int ti_hund;
};

void tc_gotoxy(int x, int y);
void tc_clrscr(void);
void tc_cprintf(const char *fmt, ...);
void tc_textcolor(int color);
void tc_textbackground(int color);
void tc_setcursortype(int type);
void tc_delay(unsigned int ms);
int  tc_getch(void);
void tc_getdate(struct date *d);
void tc_gettime(struct time *t);
int  tc_fflush(FILE *f);

/* Map the Turbo C names onto our implementations. getch/getdate/fflush are
 * macro-renamed because curses and libc already own those symbols. */
#define gotoxy         tc_gotoxy
#define clrscr         tc_clrscr
#define cprintf        tc_cprintf
#define textcolor      tc_textcolor
#define textbackground tc_textbackground
#define _setcursortype tc_setcursortype
#define delay          tc_delay
#define getch          tc_getch
#define getdate        tc_getdate
#define gettime        tc_gettime
#define fflush         tc_fflush

#ifndef _WIN32
#include <strings.h>
#define stricmp strcasecmp
#endif

#endif /* CONIO_COMPAT_H */
