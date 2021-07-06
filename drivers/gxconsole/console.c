/*
 *  $Id: hello.c,v 1.3 2006/05/22 04:53:52 debug Exp $
 *
 *  GXemul demo:  Hello World
 *
 *  This file is in the Public Domain.
 */

#include "dev_cons.h"

#define PHYSADDR_OFFSET ((signed int)0x80000000)

#define PUTCHAR_ADDRESS (PHYSADDR_OFFSET + \
						 DEV_CONS_ADDRESS + DEV_CONS_PUTGETCHAR)
#define HALT_ADDRESS (PHYSADDR_OFFSET + \
					  DEV_CONS_ADDRESS + DEV_CONS_HALT)

void printcharc(char ch)
{
	*((volatile unsigned char *)PUTCHAR_ADDRESS) = ch;
}

void halt(void)
{
	*((volatile unsigned char *)HALT_ADDRESS) = 0;
}

void printstr(char *s)
{
	while (*s)
		printcharc(*s++);
}
