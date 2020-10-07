#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
	perror(msg);;
	exit(1);
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "Not enough arguments\n");
		return 0;
	}
	
	int sockfd, newsockfd, portno;
	char buffer[256];
	
	struct sockaddr_in servAddr, cliAddr;
	socklen_t clilen;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd < 0)
	{
		error("Error opening Socket.");
	}
	bzero((char *) &servAddr, sizeof(servAddr));
	
	portno = atoi(argv[1]);
	
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = INADDR_ANY;
	servAddr.sin_port = htons(portno);
	
	if(bind(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
		error("Binding Failed.");
	
	listen(sockfd, 5);
	clilen = sizeof(cliAddr);
	
	newsockfd = accept(sockfd, (struct sockaddr *) &cliAddr, &clilen);
	
	if(newsockfd < 0)
		error("Error on Acceept");
	printf("Connected\n");
	while(1)
	{
		bzero(buffer, 255);
		int n = read(newsockfd, buffer, 255);
		if(n < 0)
			error("Error on reading.");
		printf("Client : %s", buffer);
		bzero(buffer, 255);
		fgets(buffer, 255, stdin);
		
		// fprintf(stdout, "Server: ");
		n = write(newsockfd, buffer, strlen(buffer));
		
		if(n < 0)
		{
			error("Error on Writing.");
		}
		
		int i = strncmp("Bye", buffer, 3);
		if(i==0)
			break;
		
	}
	exit(0);
		
	
}
