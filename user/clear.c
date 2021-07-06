#include "lib.h"

void umain(int argc, char **argv)
{
	if (argc != 1)
	{
		fwritef(1, "usage: clear\n");
		return;
	}
	fwritef(1, "\x1b[2J\x1b[H");
}
