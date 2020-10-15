#include "client.h"

void error(const char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

void print(const char *msg)
{
	printf("%s\n", msg);
}

int break_line(char *str, char *words[])
{
	str = strtok(str, "\n");
	
	int k = 0;
	char *ptr = strtok(str, " ");
	
	while(ptr != NULL)
	{
		words[k++] = ptr;
		ptr = strtok(NULL, " ");
	}
	return k;
}

int connect_to_server(char *ip, char *port)
{
	int portno = atoi(port);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); // Addr domain = IPv4,
	// Comm type = TCP, Protocol = Internet Protocol
	
	if(sockfd < 0)
	{
		error("Error opening socket.");
	}
	
	struct sockaddr_in servAddr;
	
	servAddr.sin_family = AF_INET;
	servAddr.sin_port =htons(portno);
	
	if(inet_pton(AF_INET, ip, &servAddr.sin_addr) < 0)
	{
		error("Invalid Address");
	}
	
	int sockconn = connect(sockfd, (struct sockaddr *)&servAddr,
	sizeof(servAddr));
	
	if(sockconn < 0)
	{
		error("Error connecting to server.");
	}
	print("Connected Successfully.");
	
	return sockfd;	
}



int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		error("Usage: ./client <server IP> <port>");
	}
	
	int sockfd;
	sockfd = connect_to_server(argv[1], argv[2]);
	
	printf("$ ");
	
	char command[1000], buffer[1000];
	char *args[10];
	while(1)
	{
		bzero(command, 1000);
		bzero(buffer, 1000);
		fgets(command, 1000, stdin);
		int cargs = break_line(command, args);
		if(cargs == 0)
		{
			printf("$ ");
			continue;
		}

		
		if(strcmp("GET",args[0]) == 0)
		{
			if(cargs != 2)
			{
				print("Invalid Syntax.");
				printf("$ ");
			}
			else {
				write(sockfd, command, strlen(command));
				read(sockfd, buffer, 1000);
				print(buffer);
			}
		}
		else if(strcmp("PUT",args[0]) == 0)
		{
			if(cargs != 2)
			{
				print("Invalid Syntax.");
				printf("$ ");
			}
			else {
				write(sockfd, command, strlen(command));
				read(sockfd, buffer, 1000);
				print(buffer);
			}
		}
		else if(strcmp("MGET",args[0]) == 0)
		{
			if(cargs != 2)
			{
				print("Invalid Syntax.");
				printf("$ ");
			}
			else {
				write(sockfd, command, strlen(command));
				read(sockfd, buffer, 1000);
				print(buffer);
			}
		}
		else if(strcmp("MPUT",args[0]) == 0)
		{
			if(cargs != 2)
			{
				print("Invalid Syntax.");
				printf("$ ");
			}
			else {
				write(sockfd, command, strlen(command));
				read(sockfd, buffer, 1000);
				print(buffer);
			}
		}
		else if(strcmp("ls",args[0]) == 0)
		{
			if(cargs != 1)
			{
				print("Invalid Syntax.");
				printf("$ ");
			}
			else {
				write(sockfd, command, strlen(command));
				read(sockfd, buffer, 1000);
				print(buffer);
			}
		}
		else if(strcmp("exit", args[0]) == 0)
		{
			if(cargs != 1)
			{
				print("Invalid Syntax.");
				printf("$ ");
			}
			print("Adios amigo.");
			break;
		}
		else {
			print("Invalid Command.");
			printf("$ ");
		}
	}
	close(sockfd);
	return 0;
}
	
	
