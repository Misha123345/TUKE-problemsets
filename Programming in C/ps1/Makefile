CC=gcc
CFLAGS=-std=c11 -Wall -Werror -g
LDLIBS=-lm
OUTPUT=ps1

all: ${OUTPUT}
	echo "Compiling..."
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c

${OUTPUT}: main.o playfair.o bmp.o
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

main.o:
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

bmp.o:
	$(CC) $(CFLAGS) -c bmp.c $(LDLIBS) -o bmp.o

playfair.o:
	$(CC) $(CFLAGS) -c playfair.c $(LDLIBS) -o playfair.o

clean: 
	rm *.o ps1

reverse.o: reverse.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

test: reverse.o test_reverse.o
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@
	./test

test_reverse.o: test_reverse.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

bmp: bmp.c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@
