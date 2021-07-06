#include "lib.h"

void umain(int argc, char **argv)
{
	if (argc != 2)
	{
		fwritef(1, "usage: touch file_name\n");
		return;
	}
	int fd = open(argv[1], O_RDONLY);
	if (fd >= 0)
	{
		fwritef(1, "file duplicated\n");
		return;
	}
	if (create(argv[1], FTYPE_REG) < 0)
	{
		fwritef(1, "fail to create file\n");
	}
}
