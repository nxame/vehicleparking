# AGENTS.md

## What this is
Vehicle Parking System — a college C project (Islington College, CPG102
'C' Programming, Term 3 2011), revived to build and run natively on
macOS/Linux/Windows. Console app for logging vehicle entry/exit and
computing parking charges.

## Build & run
- `make` then `make run` (see CONTRIBUTING.md for per-OS setup).
- Login: `admin` / `admin`. Terminal must be ≥80×25, UTF-8.
- `PARKING.C` + `conio_compat.h/.c` (Turbo C DOS API on curses) + Makefile.
- The Makefile passes `-x c`: the uppercase `.C` extension otherwise makes
  clang compile it as C++.

## Repo & git conventions
- Default branch: `main`. Active work happens on `dev`.
- Tag `college-submission` (commit 2f420a9, backdated to 2013) is the
  frozen, as-graded original — includes the DOS `PARKING.EXE`/`OBJ`/`BAK`/
  `PIF` binaries since removed from the tree. Never modify this tag.
- The user runs git push/auth/tag commands themselves — provide plain git
  commands (no gh CLI), don't execute them.
- No added code comments — keep edits bare; rationale goes in
  CONTRIBUTING.md or commit messages.

## Porting rules
- Port, not rewrite: keep 2011 logic, screen layout (reference:
  OUTLINE.png), and quirks — recursive menu navigation, float-encoded
  times (`HH.MM` as float), binary struct records in
  `VL-DATA/listVhcl.txt` — unless they crash.
- Portability edits already made: `time()`→`currTime()`, `int main`,
  forward-slash paths, `printf`→`cprintf` in `date()`, 20-char input caps,
  `searchVehicle()` recursion→loop with fclose on all exit paths, no
  `fclose(NULL)` in `autoKeyGenerate()`.
- Behavior changes: splash waits for Enter; Tab advances login fields;
  menu 5 = logout, Q = quit; NXA logo; `getch` draws its own underscore
  cursor on input fields (terminal cursors vanish on white).
- Branding edits: header is just "PARKING SYSTEM"; "NLIC" removed
  everywhere; author "Shekhar K. Sharma"; site https://shekhar.net.np/;
  college https://islington.edu.np/.
