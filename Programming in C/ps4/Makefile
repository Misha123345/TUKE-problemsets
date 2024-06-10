CC=gcc
CFLAGS=-Wall -Werror -std=c11 -g
LDLIBS=-lm
OUTPUT=bmp

all: bmp.o transformations.o main.o
	$(CC) $(CFLAGS) $^ -o $(OUTPUT) $(LDLIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDLIBS)

bmp.o: bmp.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDLIBS)

transformations.o: transformations.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDLIBS)

clean:
	rm -rf *.o $(OUTPUT)
