# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O0

# Cross-compiler and flags for cross-compilation
CROSS_COMPILER = aarch64-none-linux-gnu-
CROSS_CC = $(CROSS_COMPILER)gcc
CROSS_CFLAGS = $(CFLAGS)

writer: writer.o
	cc writer.o -o writer

writer.o: writer.c
	cc -c writer.c -o writer.o

clean:
	rm -f writer
	rm -f writer.o
	rm -f CROSS_writer #change this to whatever name changes to

CROSS_COMPILE: writer.c
	#unsure of what the - after gnu is supposed to do
	#aarch64-none-linux-gnu-gcc CROSS_writer #not sure what name test wants
	$(CROSS_CC) $(CROSS_CFLAGS) -o cross_writer writer.c
