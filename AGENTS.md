# AGENTS.md

## What this is
NLIC Vehicle Parking System — a college C project (Islington College, CPG102
'C' Programming, Term 3 2011). Console app for logging vehicle
entry/exit and computing parking charges. Being revived to run on modern
macOS (Apple Silicon).

## Repo layout & git conventions
- Default branch: `main`. Active work happens on `dev`.
- Tag `college-submission` (at commit 2f420a9, backdated to 2013) is the
  frozen, as-graded original — includes the old `PARKING.EXE`, `PARKING.OBJ`,
  `PARKING.BAK`, `PARKING.PIF` binaries that were since removed from the
  working tree. Never modify or move this tag.
- `.gitignore` excludes build artifacts (`*.exe`, `*.obj`, `*.BAK`, etc.),
  `.DS_Store`, and `.serena/` (MCP tooling state).
- User runs git push/auth commands themselves — provide commands, don't run
  push or destructive git operations unprompted.

## Original stack (does not run as-is on macOS)
- Written for **Turbo C / Borland C on DOS** (`PARKING.C`).
- Uses DOS-only APIs: `conio.h`, `dos.h`, `gotoxy`, `cprintf`, `textcolor`,
  `textbackground`, `getch`, `_setcursortype`, `getdate`, `gettime`.
- Data is stored as raw binary struct records in `VL-DATA/listVhcl.txt`
  (written via `fread`/`fwrite` on a `struct vehicles`).
- Login is hardcoded: username `masta`, password `cpdor`.

## Revival paths
1. **Run unmodified**: use DOSBox (or similar x86 DOS emulator) to run the
   original `PARKING.EXE` (available in the `college-submission` tag).
2. **Port natively** (preferred): rewrite the conio/dos calls using a
   portable library (e.g. ncurses for `gotoxy`/`cprintf`/`textcolor`/`getch`,
   standard `time.h` for date/time) so it compiles with clang on macOS.

## Porting notes
- `main()` is declared `void main()` (non-standard) — needs to become
  `int main(void)` for a portable build.
- Struct `vehicles` mixes `float` fields for time (`entry`/`exit` stored as
  `HH.MM`-ish float, not real time values) — understand this before touching
  the charge calculation logic.
- File paths use Windows-style backslashes (`"VL-DATA\\listVhcl.txt"`).
- `fflush(stdin)` is used throughout — undefined behavior outside DOS
  compilers; replace when porting.
