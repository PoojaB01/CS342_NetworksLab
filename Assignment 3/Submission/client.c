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

int send_file(int sockfd, char *filename)
{
	printf("Sending %s. \n", filename);
	char filepath[256];
	bzero(filepath, 256);
	strcpy(filepath, DSK);
	strcat(filepath, filename);
	
	FILE *fd = fopen(filepath, "r");
	
	char buffer[1024];
	
	read(sockfd, buffer, 1024);
		
	if(fd == NULL)
	{
		write(sockfd, "ABORT", 5);
		read(sockfd, buffer, 1024);
		print("File does not exist.");
		return -1;
	}
	
	write(sockfd, "OK", 2);
	
	bzero(buffer, 1024);
	read(sockfd, buffer, 1024);
	
	if(strcmp(buffer, "EXIST") == 0)
	{
		bzero(buffer, 1024);
		sprintf(buffer, "%s already exists on the server. Do you want to overwrite? (Y / N)", filename);
		print(buffer);
		
		bzero(buffer, 1024);
		fgets(buffer, 1024, stdin);
		if(buffer[0] != 'Y')
		{
			write(sockfd, "ABORT", 5);
			read(sockfd, buffer, 1024);
			print("Aborting.");
			fclose(fd);
			return -1;
		}
		else {
			write(sockfd, "OK", 2);
			bzero(buffer, 1024);
			read(sockfd, buffer, 1024);
		}
	}
	
	if(strcmp(buffer, "OK") != 0)
	{
		print("Error creating file on server.");
		fclose(fd);
		return -1;
	}
	
	int size;
	do {
		bzero(buffer, 1024);
		size = fread(buffer, sizeof(char), 1024, fd);
		write(sockfd, buffer, size);
	} while(size == 1024);
	
	read(sockfd, buffer, 1024);

	fclose(fd);
		
	bzero(buffer, 1024);
	sprintf(buffer, "Successfully sent file %s.", filename);
	print(buffer);
	
	return 0;
}

int fetch_file(int sockfd, char *filename)
{
	char buffer[1024];
	bzero(buffer, 1024);
	read(sockfd, buffer, 1024);
	if(strcmp("OK", buffer) != 0)
	{
		print(buffer);
		return -1;
	}
	
	char filepath[256];
	bzero(filepath, 256);
	strcpy(filepath, DSK);
	strcat(filepath, filename);
	
	FILE *fd = fopen(filepath, "r");
	
	if(fd != NULL)
	{
		sprintf(buffer, "%s already exists. Do you want to overwrite? (Y / N)", filename);
		print(buffer);
		fgets(buffer, 1024, stdin);
		if(buffer[0] != 'Y')
		{
			write(sockfd, "ABORT", 5);
			read(sockfd, buffer, 1024);
			print("Aborting.");
			return -1;
		}
	}
	
	fd = fopen(filepath, "w");
	
	if(fd == NULL)
	{
		write(sockfd, "ABORT", 5);
		read(sockfd, buffer, 1024);
		print("Error creating file.");
		return -1;
	}
	
	write(sockfd, "OK", 1024);
	
	
	while(1)
	{
		bzero(buffer, 1024);
		read(sockfd, buffer, 1024);
		fwrite(buffer, sizeof(char), strlen(buffer), fd);
		if(strlen(buffer) < 1024)
			break;
	}
	fclose(fd);
	bzero(buffer, 1024);
	sprintf(buffer, "Successfully recieved file %s.", filename);
	print(buffer);
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
	write(sockfd, "OK", 2);
	bzero(buffer, 256);
	read(sockfd, buffer, 256);
	print(buffer);
	return 0;
}


int send_files_with_ext(int sockfd, char *extension)
{
	char buffer[256];
	read(sockfd, buffer, 256);
	
	DIR *di;
	struct dirent *dir;
	di = opendir(DSK);
	char *filename;
	char *ext;
	
	while ((dir = readdir(di)) != NULL) {
		filename = dir->d_name;
		if(filename == NULL)
		continue;
		ext = strtok(filename, ".");
		if(ext == NULL)
		continue;
		ext = strtok(NULL, ".");
		if(ext != NULL && strcmp(ext, extension) == 0)
		{
			strcat(filename, ".");
			strcat(filename, extension);
			write(sockfd, filename, strlen(filename));
			send_file(sockfd, filename);
			// break;
		}
	}
	
	write(sockfd, "DONE", 4);
	read(sockfd, buffer, 256);
	return 1;		
}

int fetch_files_with_ext(int sockfd, char *extension)
{
	char buffer[256];
	while(1)
	{
		bzero(buffer, 256);
		read(sockfd, buffer, 256);
		if(strcmp(buffer, "DONE") == 0)
			break;
		write(sockfd, "OK", 2);
		fetch_file(sockfd, buffer);
		write(sockfd, "OK", 2);
	}
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
				read(sockfd, buffer, 1000);
				if(strcmp("OK", buffer))
				{
					print("ERROR");
					continue;
				}
				write(sockfd, args[1], strlen(args[1]));
				
				fetch_file(sockfd, args[1]);
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
				
				send_file(sockfd, args[1]);
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
				
				send_files_with_ext(sockfd, args[1]);
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
				write(sockfd, args[1], strlen(args[1]));
				fetch_files_with_ext(sockfd, args[1]);
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

	
	
