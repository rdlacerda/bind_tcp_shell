#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <getopt.h>

#define TRUE 1

void on_error(int, const char *, int);
int get_tcp_socket(void);
void bind_tcp_port(int,int);
