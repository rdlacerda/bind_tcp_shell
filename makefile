CC=gcc
CFLAGS=-I.

reverse_bind_shell: bind_shell.c bind_shell.h
	$(CC) -o bind_shell bind_shell.c $(CFLAGS) 