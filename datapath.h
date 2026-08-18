/*
 * datapath.h — per-user data location for the parking records.
 *
 * The DOS original wrote VL-DATA/listVhcl.txt next to the binary; a
 * downloaded release binary has no such folder and may sit somewhere
 * read-only, so the data now lives in the platform's user-data directory:
 *
 *   macOS    ~/Library/Application Support/vehicleparking/listVhcl.txt
 *   Linux    $XDG_DATA_HOME/vehicleparking/listVhcl.txt
 *            (default ~/.local/share/vehicleparking/)
 *   Windows  %APPDATA%\vehicleparking\listVhcl.txt
 *
 * dataFile() computes the path once, creates the directory if needed,
 * and returns the full path to listVhcl.txt. If HOME/APPDATA is unset
 * it falls back to the original relative VL-DATA/ behavior.
 */
#ifndef DATAPATH_H
#define DATAPATH_H

const char *dataFile(void);

#endif
