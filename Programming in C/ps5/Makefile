CC=gcc
CFLAGS=-Wall -Werror -std=c11 -Wconversion -g
LDLIBS=-lm
OUTPUT=adventure

all: backpack.o command.o container.o game.o item.o main.o parser.o room.o world.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) $^ -o $(OUTPUT) $(LDLIBS)
	@make -s clear

main.o: main.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDLIBS)

backpack.o: backpack.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDLIBS)

command.o: command.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDLIBS)

container.o: container.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDLIBS)

game.o: game.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDLIBS)

item.o: item.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDLIBS)

parser.o: parser.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDLIBS)

room.o: room.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDLIBS)

world.o: world.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDLIBS)

clean:
	rm -rf *.o $(OUTPUT)

clear:
	rm -rf *.o
