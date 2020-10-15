#include "server.h"


void error(const char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

void print(const char *msg)
{
	printf("%s\n", msg);
}

int setup_server(char *port)
{
	int portno = atoi(port);
	
	int servfd = socket(AF_INET, SOCK_STREAM, 0); // Addr domain = IPv4,
	// Comm type = TCP, Protocol = Internet Protocol
	
	if(servfd < 0)
	{
		error("Error opening socket.");
	}
	
	struct sockaddr_in servAddr;
	
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = INADDR_ANY;
	servAddr.sin_port = htons(portno);
	
	if(bind(servfd, (struct sockaddr *)&servAddr, sizeof(servAddr)))
	{
		error("Bind failed. Possibly invalid Port Number.");
	}
	
	listen(servfd, 5);
	
	print("Server up and listening.");	
	
	return servfd;
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		error("Usage: ./server <port>");
	}
	int serv = setup_server(argv[1]);
	
	struct sockaddr_in cliAddr;
	socklen_t clilen;
	
	clilen = sizeof(cliAddr);
	
	int clifd = accept(serv, (struct sockaddr *) &cliAddr, &clilen);
	
	if(clifd < 0)
	{
		error("Error connecting.");
	}
	
	print("Connected.");
	
	char buffer[1000];
	char *args[10];
	while(1)
	{
		bzero(buffer, 1000);
		int n = read(clifd, buffer, 1000);
		print(buffer);
		n = write(clifd, buffer, strlen(buffer));
	}
	return 0;
}
