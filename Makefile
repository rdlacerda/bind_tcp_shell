CC=gcc
CFLAGS=-I.
DEPS=server.h
OBJ=server.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
