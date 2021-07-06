/* See COPYRIGHT for copyright information. */

/* The Run Time Clock and other NVRAM access functions that go with it. */
/* The run time clock is hard-wired to IRQ8. */

#include <kclock.h>

extern void set_timer();

void kclock_init(void)
{
	set_timer();
}
