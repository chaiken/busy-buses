/*
 * lsi2c implementation for busybox
 *
 * Copyright (C) 2013, 2014 Alison Chaiken alison@she-devel.com,
 *                          Souf Oued souf_oued@yahoo.fr
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */

//usage:#define lsi2c_trivial_usage NOUSAGE_STR
//usage:#define lsi2c_full_usage ""

#include "libbb.h"

static int FAST_FUNC fileAction(
				const char *instring,
				struct stat *statbuf UNUSED_PARAM,
				void *userData UNUSED_PARAM,
				int depth)
{
	const char *sysfs_node, *drivername;
	char *address;

	sysfs_node = bb_basename(instring);

	if (!isdigit(sysfs_node[0])) {
		depth++;
		return depth;
	}

	drivername = bb_basename(dirname((char *)instring));
	address = strchr(sysfs_node, '-');

	if (*address++)
		printf("Controller %c for driver %s at address 0x%s.\n", *sysfs_node,
		   drivername, address);

	return 0;
}

int lsi2c_main(int argc, char **argv) MAIN_EXTERNALLY_VISIBLE;
int lsi2c_main(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{
	const char *fileName = "/sys/bus/i2c/drivers";
	int depth = 0;

	recursive_action(fileName,
				ACTION_RECURSE,
				fileAction,
				NULL, /* dirAction */
				NULL, /* userData */
				depth);

	return EXIT_SUCCESS;
}
