#include "lib.h"

void umain(int argc, char **argv)
{
	if (argc == 1)
	{
		fwritef(1, "usage: rm file_1 [file_2... file_n]\n");
		return;
	}
	int i;
	struct Stat state;
	for (i = 1; i < argc; ++i)
	{
		if (stat(argv[i], &state) < 0)
		{
			fwritef(1, "cannot open file: %s\n", argv[i]);
			continue;
		}
		if (state.st_type != FTYPE_REG)
		{
			fwritef(1, "specified path should be file\n", argv[i]);
			continue;
		}
		remove(argv[i]);
	}
}
