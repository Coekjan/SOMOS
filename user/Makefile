INCLUDES = -I../include/

#CROSS_COMPILE := /usr/eldk/usr/bin/mips_4KC-
#CC           := $(CROSS_COMPILE)gcc
#CFLAGS       := -O -G 0 -mno-abicalls -fno-builtin -Wa,-xgot -Wall -fPIC
#LD           := $(CROSS_COMPILE)ld
# For embedding one program in another

USERLIB := printf.o \
		print.o \
		libos.o \
		fork.o \
		pgfault.o \
		syscall_lib.o \
		ipc.o \
		string.o \
		fd.o \
		pageref.o \
		file.o \
		pipe.o \
		fsipc.o \
		wait.o \
		spawn.o \
		console.o \
		fprintf.o

CFLAGS += -nostdlib -static


all: pingpong.x echo.x echo.b  num.x num.b idle.x icode.x init.b sh.b cat.b ls.b tree.x tree.b mkdir.x mkdir.b touch.x touch.b rm.x rm.b history.b history.x counter.x counter.b sum.x sum.b $(USERLIB) entry.o syscall_wrap.o

%.x: %.b.c 
	echo cc1 $< 
	$(CC) $(CFLAGS) -c -o $@ $<

%.b.c: %.b
	echo create $@
	echo bintoc $* $< > $@~
	chmod +x ./bintoc
	./bintoc $* $< > $@~ && mv -f $@~ $@
#   grep \. $@
	
%.b: entry.o syscall_wrap.o %.o $(USERLIB)
	echo ld $@
	$(LD) -o $@ $(LDFLAGS) -G 0 -static -n -nostdlib -T ./user.lds $^

%.o: %.c
	echo user1 cc $<
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

%.o: %.S
	echo as $<
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

%.o: lib.h

.PHONY: clean

clean:
	rm -rf *~ *.o *.b.c *.x *.b

include ../include.mk
