#include "lib.h"

void umain(int argc, char **argv)
{
	if (argc != 1)
	{
		fwritef(1, "usage: history\n");
		return;
	}
	int his = open(".history", O_RDONLY | O_CREAT);
	char ch;
	fwritef(1, "\x1b[33m-*- HISTORY -*-\x1b[0m\n");
	fwritef(1, "\x1b[33m1\x1b[0m\t");
	int cnt = 1;
	int fl = 0;
	while (read(his, &ch, 1) == 1)
	{
		if (fl)
		{
			fwritef(1, "\x1b[33m%d\x1b[0m\t", cnt);
			fl = 0;
		}
		fwritef(1, "%c", ch);
		if (ch == '\n')
		{
			cnt++;
			fl = 1;
		}
	}
}
