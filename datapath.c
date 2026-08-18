/*
 * datapath.c — see datapath.h.
 */
#include "datapath.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define makeDir(p) _mkdir(p)
#else
#include <sys/stat.h>
#define makeDir(p) mkdir(p, 0755)
#endif

const char *dataFile(void)
{
	static char path[512];
	char *base;

	if (path[0] != '\0')
		return path;

#ifdef _WIN32
	base = getenv("APPDATA");
	if (base != NULL)
		snprintf(path, sizeof path, "%s\\vehicleparking", base);
#elif defined(__APPLE__)
	base = getenv("HOME");
	if (base != NULL)
		snprintf(path, sizeof path,
			 "%s/Library/Application Support/vehicleparking", base);
#else
	base = getenv("XDG_DATA_HOME");
	if (base != NULL && base[0] != '\0') {
		snprintf(path, sizeof path, "%s/vehicleparking", base);
	} else {
		base = getenv("HOME");
		if (base != NULL) {
			snprintf(path, sizeof path, "%s/.local", base);
			makeDir(path);
			strcat(path, "/share");
			makeDir(path);
			strcat(path, "/vehicleparking");
		}
	}
#endif
	if (path[0] == '\0')
		strcpy(path, "VL-DATA");
	makeDir(path);
	strcat(path, "/listVhcl.txt");
	return path;
}
