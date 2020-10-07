#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
	perror(msg);;
	exit(1);
}

int main(int argc, char* argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in servAddr;
	struct hostent *server;
	
	char buffer[256];
	
	if(argc < 3)
	{
		fprintf(stderr, "Not enough arguments\n");
		return 0;
	}
	
	portno  = atoi(argv[2]);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd < 0)
		error("Error opening socket");
		
	server = gethostbyname(argv[1]);
	if(server == NULL)
	{
		fprintf(stderr, "Error, no such host");
	}
	bzero((char *) &servAddr, sizeof(servAddr));
	servAddr.sin_family =  AF_INET;
	bcopy((char *) server->h_addr, (char *) &servAddr.sin_addr.s_addr, server->h_length);
	servAddr.sin_port = htons(portno);
	
	if(connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
		error("Connection Failed");
	printf("Connected\n");
	while(1) 
	{
		bzero(buffer, 255);
		fgets(buffer, 255, stdin);
		
		// fprintf(stdout, "Client: ");
		n = write(sockfd, buffer, strlen(buffer));
		
		if(n < 0)
		{
			error("Error on Writing.");
		}
		
		bzero(buffer, 255);
		int n = read(sockfd, buffer, 255);
		if(n < 0)
			error("Error on reading.");
		printf("Server : %s", buffer);
		
		
		int i = strncmp("Bye", buffer, 3);
		if(i==0)
			break;
	}
	
	close(sockfd);
	return 0;
	
	
}
