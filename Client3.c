#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>		//inet_addr

int main(int argc, char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char *message;
	char server_reply[2000];

	//Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_desc == -1)
	{
		printf("Could not create socket");
	}

	server.sin_addr.s_addr = inet_addr("192.168.1.10");
	server.sin_family = AF_INET;
	server.sin_port = htons( 22 );

	//Connect to remote server
	if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0 )
	{
		puts("Connect Error\n");
		return 1;
	}

	puts("Connected");

	//Send some data
	message = "Connect";

	if(send(socket_desc, message, strlen(message), 0) < 0 )
	{
		puts("Send Failed");
		return 1;
	}

	puts("Data Send\n");

	//Receive a reply from the server
	if(recv(socket_desc, server_reply, 2000, 0) < 0 )
	{
		puts("Receiver failed");
	}

	puts("Reply Received Successfully");
	puts(server_reply);

//	close(socket_desc);

	return 0;
}
