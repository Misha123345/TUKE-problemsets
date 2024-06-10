CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wconversion -g
LDLIBS=-lm -lcurses
OUTPUT=game

all: $(OUTPUT)

$(OUTPUT): main.o k.o ui.o hof.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) main.o k.o ui.o hof.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

k.o: k.c
	$(CC) $(CFLAGS) -c k.c $(LDLIBS) -o k.o

ui.o: ui.c
	$(CC) $(CFLAGS) -c ui.c $(LDLIBS) -o ui.o

hof.o: hof.c
	$(CC) $(CFLAGS) -c hof.c $(LDLIBS) -o hof.o

clean:
	rm -rf $(OUTPUT) *.o
