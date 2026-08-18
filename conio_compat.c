/*
 * conio_compat.c — see conio_compat.h.
 * Curses-backed implementation of the Turbo C DOS console API.
 */
#include "conio_compat.h"

/* We implement the tc_* functions here, so drop the renaming macros and the
 * fflush override before pulling in the real headers. */
#undef gotoxy
#undef clrscr
#undef cprintf
#undef textcolor
#undef textbackground
#undef _setcursortype
#undef delay
#undef getch
#undef getdate
#undef gettime
#undef fflush

#define _XOPEN_SOURCE_EXTENDED 1
#include <curses.h>
#include <locale.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int cur_fg = LIGHTGRAY; /* DOS default */
static int cur_bg = BLACK;
static int initialized = 0;
static int cursor_visible = 0;

/* CP437 -> UTF-8 for the characters PARKING.C actually prints. */
static const char *cp437_utf8(unsigned char c)
{
	switch (c) {
	case 185: return "╣"; /* ╣ */
	case 186: return "║"; /* ║ */
	case 187: return "╗"; /* ╗ */
	case 188: return "╝"; /* ╝ */
	case 200: return "╚"; /* ╚ */
	case 201: return "╔"; /* ╔ */
	case 204: return "╠"; /* ╠ */
	case 205: return "═"; /* ═ */
	case 219: return "█"; /* █ */
	default:  return NULL;
	}
}

static void shutdown_curses(void)
{
	if (initialized) {
		endwin();
		fputs("\033[0 q", stdout);
		fflush(stdout);
		initialized = 0;
	}
}

static void ensure_init(void)
{
	if (initialized)
		return;
	setlocale(LC_ALL, "");
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	if (has_colors()) {
		short fg, bg;
		start_color();
		/* One pair per (fg 0-7, bg 0-7) combo; bright fg adds A_BOLD. */
		for (fg = 0; fg < 8; fg++)
			for (bg = 0; bg < 8; bg++)
				init_pair((short)(fg * 8 + bg + 1), fg, bg);
	}
	initialized = 1;
	atexit(shutdown_curses);
}

/* Borland color index -> curses COLOR_* (low 3 bits differ in order). */
static short curses_color(int c)
{
	static const short map[8] = {
		COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN,
		COLOR_RED, COLOR_MAGENTA, COLOR_YELLOW /* brown */, COLOR_WHITE
	};
	return map[c & 7];
}

static chtype cur_attr(void)
{
	short fg = curses_color(cur_fg);
	short bg = curses_color(cur_bg);
	chtype a = COLOR_PAIR(fg * 8 + bg + 1);
	if (cur_fg > 7)
		a |= A_BOLD;
	return a;
}

void tc_gotoxy(int x, int y)
{
	ensure_init();
	move(y - 1, x - 1);
}

void tc_clrscr(void)
{
	ensure_init();
	bkgdset(cur_attr() | ' ');
	erase();
	move(0, 0);
	refresh();
}

void tc_cprintf(const char *fmt, ...)
{
	char buf[1024];
	unsigned char *p;
	va_list ap;

	ensure_init();
	va_start(ap, fmt);
	vsnprintf(buf, sizeof buf, fmt, ap);
	va_end(ap);

	attrset(cur_attr());
	for (p = (unsigned char *)buf; *p; p++) {
		const char *u = cp437_utf8(*p);
		if (u)
			addstr(u);
		else
			addch(*p);
	}
	refresh();
}

void tc_textcolor(int color)
{
	cur_fg = color & 15;
}

void tc_textbackground(int color)
{
	cur_bg = color & 7;
}

void tc_setcursortype(int type)
{
	ensure_init();
	cursor_visible = (type != _NOCURSOR);
	curs_set(cursor_visible ? 1 : 0);
	refresh();
	if (cursor_visible)
		fputs(type == _SOLIDCURSOR ? "\033[1 q" : "\033[3 q", stdout);
	fflush(stdout);
}

void tc_delay(unsigned int ms)
{
	ensure_init();
	refresh();
	napms((int)ms);
}

int tc_getch(void)
{
	int c, y, x;
	int have_saved = 0;
	cchar_t saved;

	ensure_init();
	refresh();

	/* Terminal cursors can be invisible on the solid-white input fields,
	 * so draw our own DOS-style underscore cursor and restore the cell
	 * after the keypress. */
	if (cursor_visible) {
		getyx(stdscr, y, x);
		if (in_wch(&saved) == OK)
			have_saved = 1;
		attrset(cur_attr() | A_BLINK);
		addch('_');
		move(y, x);
		refresh();
	}

	c = getch();

	if (have_saved) {
		move(y, x);
		add_wch(&saved);
		move(y, x);
		refresh();
	}

	/* Normalize to the DOS key codes PARKING.C expects. */
	if (c == KEY_BACKSPACE || c == 127)
		return 8;
	if (c == KEY_ENTER || c == '\n' || c == '\r')
		return 13;
	return c;
}

void tc_getdate(struct date *d)
{
	time_t now = time(NULL);
	struct tm *tm = localtime(&now);
	d->da_year = tm->tm_year + 1900;
	d->da_mon = tm->tm_mon + 1;
	d->da_day = tm->tm_mday;
}

void tc_gettime(struct time *t)
{
	time_t now = time(NULL);
	struct tm *tm = localtime(&now);
	t->ti_hour = tm->tm_hour;
	t->ti_min = tm->tm_min;
	t->ti_sec = tm->tm_sec;
	t->ti_hund = 0;
}

/* DOS code calls fflush(stdin) to drop pending keystrokes; that's undefined
 * behavior on modern libcs, so route it to curses' input flush instead. */
int tc_fflush(FILE *f)
{
	if (f == stdin) {
		if (initialized)
			flushinp();
		return 0;
	}
	return fflush(f);
}
