#include "fileio.h"
#include "debug.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <libgen.h> /* TODO: dirname */
#include <sys/file.h>

/* TODO: Revisit these - they're almost identical */

int create_tup_file(const char *tup, const char *path)
{
	int rc;
	char filename[] = ".tup/XXXXXX/" SHA1_X;

	/* TODO: Don't hardcode, make sure it only matches the end? */
	if(strstr(path, "Makefile") != NULL) {
		char *dir;
		dir = strdup(path);
		dir = dirname(dir);
		if(create_dir_file(dir) < 0)
			return 1;
	}
	memcpy(filename + 5, tup, 6);
	tupid_from_filename(filename + 12, path);

	DEBUGP("create tup file: %s\n", filename);
	rc = create_if_not_exist(filename);
	return rc;
}

int create_tup_file_tupid(const char *tup, const tupid_t tupid)
{
	int rc;
	char filename[] = ".tup/XXXXXX/" SHA1_X;

	memcpy(filename + 5, tup, 6);
	memcpy(filename + 12, tupid, sizeof(tupid_t));

	DEBUGP("create tup file: %s\n", filename);
	rc = create_if_not_exist(filename);
	return rc;
}
