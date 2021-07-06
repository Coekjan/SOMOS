#include "lib.h"

char buf[8192];

void cat(int f, char *s)
{
	long n;
	int r;

	while ((n = read(f, buf, (long)sizeof buf)) > 0)
		if ((r = write(1, buf, n)) != n)
			user_panic("write error copying %s: %e", s, r);
	if (n < 0)
		user_panic("error reading %s: %e", s, n);
}

void umain(int argc, char **argv)
{
	int f, i;
	struct Stat st;
	if (argc == 1)
		cat(0, "<stdin>");
	else
		for (i = 1; i < argc; i++)
		{
			if (stat(argv[i], &st) < 0)
			{
				writef("cannot open file: %s\n", argv[i]);
				continue;
			}
			else if (st.st_type != FTYPE_REG)
			{
				writef("specified path should be file\n");
				continue;
			}
			f = open(argv[i], O_RDONLY);
			cat(f, argv[i]);
			close(f);
		}
}
