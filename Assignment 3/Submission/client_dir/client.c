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

int send_file(int sockfd, char *fi X˜Ä­ ÕÙøÔd¸…pã¥ªlename)
{
	return 0;
}

int fetch_file(int sockfd, char *filename)
{
	return 0;
}


int ls(int sockfd)
{
	char buffer[256];
	while(1) {
		bzero(buffer, 256);
		read(sockfd, buffer, 256);
		
		if(strcmp(buffer, "DONE") == 0)
		break;
		
		print(buffer);
		
		write(sockfd, "OK", 2);
	}
	
	bzero(buffer, 256);
	read(sockfd, buffer, 256);
	print(buffer);
	return 0;
}



int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		error("Usage: ./client <server IP> <port>");
	}
	
	int sockfd;
	sockfd = connect_to_server(argv[1], argv[2]);
	
	char command[1000], buffer[1000];
	char *args[10];
	
	while(1)
	{
		bzero(command, 1000);
		bzero(buffer, 1000);
		
		printf("$ ");
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
			}
			else {
				write(sockfd, args[0], strlen(args[0]));
				
				bzero(buffer, 1000);
				read(sockfd, buffer, 1 X˜Ä­000); ÕÙ
				iøÔd¸…f(strpã¥ªcmp("OK", buffer))
				{
					print("ERROR");
					continue;
				}
				write(sockfd, args[1], strlen(args[1]));
				
				bzero(buffer, 1000);
				read(sockfd, buffer, 1000);
				
				print(buffer);
			}
		}
		else if(strcmp("PUT",args[0]) == 0)
		{
			if(cargs != 2)
			{
				print("Invalid Syntax.");
			}
			else {
				write(sockfd, args[0], strlen(args[0]));
				
				bzero(buffer, 1000);
				read(sockfd, buffer, 1000);
				if(strcmp("OK", buffer))
				{
					print("ERROR");
					continue;
				}
				write(sockfd, args[1], strlen(args[1]));
				
				bzero(buffer, 1000);
				read(sockfd, buffer, 1000);
				
				print(buffer);
			}
		}
		else if(strcmp("MGET",args[0]) == 0)
		{
			if(cargs != 2)
			{
				print("Invalid Syntax.");
			}
			else {
				write(sockfd, args[0], strlen(args[0]));
				
				bzero(buffer, 1000);
				read(sockfd, buffer, 1000);
				if(strcmp("OK", buffer))
				{
					print("ERROR");
					continue;
				}
				write(sockfd, args[1], strlen(args[1]));
				
				bz X˜Ä­ero(buffer ÕÙ, 1000);
			øÔd¸…	read(sockpã¥ªfd, buffer, 1000);
				
				print(buffer);
			}
		}
		else if(strcmp("MPUT",args[0]) == 0)
		{
			if(cargs != 2)
			{
				print("Invalid Syntax.");
			}
			else {
				write(sockfd, args[0], strlen(args[0]));
				
				bzero(buffer, 1000);
				read(sockfd, buffer, 1000);
				if(strcmp("OK", buffer))
				{
					print("ERROR");
					continue;
				}
				write(sockfd, args[1], strlen(args[1]));
				
				bzero(buffer, 1000);
				read(sockfd, buffer, 1000);
				
				print(buffer);
			}
		}
		else if(strcmp("ls",args[0]) == 0)
		{
			if(cargs != 1)
			{
				print("Invalid Syntax.");
			}
			else {
				write(sockfd, args[0], strlen(args[0]));
				ls(sockfd);

			}
		}
		else if(strcmp("exit", args[0]) == 0)
		{
			if(cargs != 1)
			{
				print("Invalid Syntax.");

			}
			print("Adios amigo.");
			break;
		}
		else {
			print("Invalid Command.");
		}
	}
	close(sockfd);
	return 0;
}

int fetch_file(int sockfd, char *filename)
{
		
}
	
	
