#include "lib.h"

int get_num(char *src)
{
	int num = 0;
	while (*src)
		num = (num << 1) + (num << 3) + (*src++ - '0');
	return num;
}

void umain(int argc, char **argv)
{
	int i;
	int max = 200000000;
	if (argc == 2)
	{
		max = get_num(argv[1]);
	}
	else if (argc > 2)
	{
		fwritef(1, "usage: counter [num]\n");
		return;
	}
	for (i = 0; i < max; ++i)
	{
	}
	fwritef(1, "Done: loop %d times\n", max);
}
