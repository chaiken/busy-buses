/*
 * lsi2c implementation for busybox
 *
 * Copyright (C) 2013 Alison Chaiken alison@she-devel.com
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */

//usage:#define lsspi_trivial_usage NOUSAGE_STR
//usage:#define lsspi_full_usage ""

#include "libbb.h"

static int FAST_FUNC fileAction(
		const char *fileName,
		struct stat *statbuf UNUSED_PARAM,
		void *userData UNUSED_PARAM,
		int depth UNUSED_PARAM)
{
	return TRUE;
}

int lsspi_main(int argc, char **argv) MAIN_EXTERNALLY_VISIBLE;
int lsspi_main(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{
	/* no options, no getopt */

	recursive_action("/sys/bus/spi/devices",
			ACTION_RECURSE,
			fileAction,
			NULL, /* dirAction */
			NULL, /* userData */
			0 /* depth */);

	return EXIT_SUCCESS;
}
