CFLAGS=-I. -g
CPPFLAGS=-D_LINUX_SOURCE
LDLIBS=-lcrypto
OBJS=pgdump.o comdb2rle.o crc32c.o
pgdump:$(OBJS)
comdb2rle.o:CPPFLAGS+=-DCRLE_TOOLS
crc32c.o:CFLAGS+=-msse4.2 -mpclmul
clean:
	-rm $(OBJS) pgdump
