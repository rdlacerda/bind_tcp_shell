#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>  
#include <netinet/in.h> 
#include <string.h>     

#define LISTEN_BACKLOG 3
#define TCP_PORT 33341
#define TRUE 1

void on_error(int, const char *, int);
int get_socket_tcp(void);
