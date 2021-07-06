#include "lib.h"

int flag[256];

void lsdir(char *, char *);
void ls1(char *, u_int, u_int, char *);

void ls(char *path, char *prefix)
{
	int r;
	struct Stat st;

	if ((r = stat(path, &st)) < 0)
	{
		writef("file not found\n");
		return;
	}
	if (st.st_type == FTYPE_DIR && !flag['d'])
		lsdir(path, prefix);
	else
		ls1(0, st.st_type, st.st_size, path);
}

void lsdir(char *path, char *prefix)
{
	int fd, n;
	struct File f;

	if ((fd = open(path, O_RDONLY)) < 0)
		user_panic("open %s: %e", path, fd);
	while ((n = readn(fd, &f, sizeof f)) == sizeof f)
		if (f.f_name[0] && (flag['a'] || f.f_name[0] != '.'))
			ls1(prefix, f.f_type, f.f_size, f.f_name);
	if (n > 0)
		user_panic("short read in directory %s", path);
	if (n < 0)
		user_panic("error reading directory %s: %e", path, n);
}

void ls1(char *prefix, u_int type, u_int size, char *name)
{
	char *sep;
	if (flag['l'])
		fwritef(1, "%11d %c ", size, type == FTYPE_DIR ? 'd' : type == FTYPE_BIN ? 'x'
																				 : '-');
	if (prefix)
	{
		if (prefix[0] && prefix[strlen(prefix) - 1] != '/')
			sep = "/";
		else
			sep = "";
		fwritef(1, "%s%s", prefix, sep);
	}
	fwritef(1, type == FTYPE_DIR ? "\x1b[36m%s\x1b[0m" : type == FTYPE_BIN ? "\x1b[31m%s\x1b[0m"
																		   : "%s",
			name);
	if (flag['F'] && type == FTYPE_DIR)
		fwritef(1, "/");
	if (flag['F'] && type == FTYPE_BIN)
		fwritef(1, "*");
	fwritef(1, flag['l'] ? "\n" : " ");
}

void usage(void)
{
	fwritef(1, "usage: ls [-adFl] [file...]\n");
	exit();
}

void umain(int argc, char **argv)
{
	int i;

	ARGBEGIN
	{
	default:
		usage();
	case 'a':
	case 'd':
	case 'F':
	case 'l':
		flag[(u_char)ARGC()]++;
		break;
	}
	ARGEND

	if (argc == 0)
		ls("/", "");
	else
	{
		for (i = 0; i < argc; i++)
			ls(argv[i], argv[i]);
	}
}
