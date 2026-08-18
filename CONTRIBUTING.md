# Contributing / Development Guide

A 2011 Turbo C (DOS) college project revived to build and run natively on
macOS, Linux, and Windows. The original as-graded code is frozen in the
`college-submission` git tag — this working tree is the portable version.

## First-time setup

Nothing is installed globally beyond your platform's standard C toolchain
and the curses library most systems already ship.

### macOS (Apple Silicon or Intel)

```sh
xcode-select --install   # clang, make, and system ncurses — skip if present
git clone https://github.com/nxame/vehicleparking.git
cd vehicleparking
make
make run
```

### Linux (Debian/Ubuntu)

```sh
sudo apt install build-essential libncursesw5-dev
git clone https://github.com/nxame/vehicleparking.git
cd vehicleparking
make
make run
```

Fedora/Arch: install `ncurses-devel` / `ncurses` instead.

### Windows

Two options, pick one:

- **WSL (recommended):** install WSL, then follow the Linux steps inside it.
- **MSYS2 + PDCurses:** in a MINGW64 shell,
  `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-pdcurses make`, then
  `make` in the repo (links `-lpdcurses`).

## Using a release binary

Prebuilt binaries are attached to GitHub releases as `.tar.gz` (macOS,
Linux) and `.zip` (Windows) — extract and run, no install step.

They are not code-signed. On macOS, clear the download quarantine once
before the first run:

```sh
xattr -d com.apple.quarantine ./parking
```

(Or right-click the binary → Open.) Windows SmartScreen may show a
warning the first time — choose "More info" → "Run anyway".

## Running

- Terminal must be at least **80×25** and UTF-8 (any modern default is).
- Login: username `admin`, password `admin` (hardcoded test credentials).
- Data persists as raw binary records in `listVhcl.txt` under the
  platform's user-data directory (created on first run):
  - macOS: `~/Library/Application Support/vehicleparking/`
  - Linux: `$XDG_DATA_HOME/vehicleparking/` (default
    `~/.local/share/vehicleparking/`)
  - Windows: `%APPDATA%\vehicleparking\`

  Delete the file for a fresh start. Files written by the original DOS
  build are not compatible (16-bit ints).
- `ESC` inside forms returns to the menu (or exits, on the login screen).
- `Tab` or `Enter` advances between login fields.
- Main menu: `1`–`4` for tasks, `5` logs out (back to login), `Q` quits.

## Layout

| File | Purpose |
| --- | --- |
| `PARKING.C` | Original 2011 source, minimally edited for portability |
| `conio_compat.h/.c` | Turbo C `conio.h`/`dos.h` API on top of curses |
| `datapath.h/.c` | Per-OS user-data directory for the records file |
| `Makefile` | Picks the right curses lib per OS; forces C mode (`-x c`) because the uppercase `.C` extension otherwise compiles as C++ |
| `OUTLINE.png` | Original screen-design mockup, the visual reference |

## What the compat layer covers

`gotoxy`, `clrscr`, `cprintf`, `textcolor`, `textbackground`, `getch`,
`_setcursortype`, `delay`, `getdate`, `gettime`, plus `fflush(stdin)`
rerouted to `flushinp()`. CP437 box-drawing characters (186, 201, 205,
219, …) map to Unicode so the DOS UI renders as designed.

Because terminal cursors are often invisible on the solid-white input
fields, `getch` draws its own DOS-style underscore cursor at the input
position (only when the app wants a visible cursor) and restores the cell
after each keypress. The terminal's real cursor style is also nudged to
blinking via DECSCUSR and restored on exit.

## Portability edits made to PARKING.C

- `time()` renamed `currTime()` (libc clash)
- `void main` → `int main`
- `\\` path separators → `/`
- one stray `printf` → `cprintf` (output must go through curses)
- input loops bounded at 20 chars (was an unchecked stack buffer; 20
  matches the smallest destination buffers and the UI field width)
- `searchVehicle()` converted from tail recursion to a loop (was an
  infinite-recursion warning and unbounded stack growth), with the file
  handle now closed on the not-found and already-released paths
- removed a `fclose(NULL)` in `autoKeyGenerate()` (crashes glibc/MSVCRT
  on first run when no data file exists)

## Behavior changes since the original

- Credentials changed to `admin`/`admin`
- Splash waits for `Enter` after loading instead of auto-advancing
- `Tab` also advances/submits input fields (was Enter only)
- Menu option 5 is now LOGOUT (returns to login); new `Q` option quits
- Logo reads NXA; "NLIC" branding removed; typo fixes in screen text

## Ground rules

- This is a port, not a rewrite: keep the 2011 logic, screen layout, and
  quirks (recursive menu navigation, float-encoded times) unless they crash.
- Compare UI changes against `OUTLINE.png`.
- Never touch the `college-submission` tag.
- Work on `dev`; `main` is the default branch.
