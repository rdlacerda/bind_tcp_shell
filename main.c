#include "server.h"

int main(int argc, char * argv[])
{
  int listen_tcp_port, queue_connection_size;
  int next_parser_option;

  const char * short_options = "p:q:";
  struct option long_options[] = {
    {"port", 1, NULL, 'p'},
    {"queue", 1, NULL, 'q'}};
  
 do
 {
  next_parser_option = getopt_long(argc, argv, short_options, long_options, NULL);
  
  switch(next_parser_option)
  {
    case 'p':
      listen_tcp_port = atoi(optarg);
      break;
    case 'q':
      queue_connection_size = atoi(optarg);
      break;
  }
 } while(next_parser_option != -1); 

	bind_tcp_port(listen_tcp_port, queue_connection_size);
	return 0;
}
