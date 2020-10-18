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

int send_file(int sockfd, char *filename)
{
	char filepath[256];
	bzero(filepath, 256);
	strcpy(filepath, DSK);
	strcat(filepath, filename);
	
	FILE *fd = fopen(filepath, "r");
	
	char buffer[1024];
	
	if(fd == NULL)
	{
		bzero(buffer, 1024);
		sprintf(buffer, "%s not found.", filename);
		write(sockfd, buffer, strlen(buffer));
		return -1;
	}
	write(sockfd, "OK", 2);
	
	bzero(buffer, 1024);
	read(sockfd, buffer, 1024);
	if(strcmp("OK", buffer) != 0)
	{
		write(sockfd, "ABORT", 5);
		fclose(fd);
		return -1;
	}
	
	int size;
	do {
		bzero(buffer, 1024);
		size = fread(buffer, sizeof(char), 1024, fd);
		write(sockfd, buffer, size);
	} while(size == 1024);
	
	fclose(fd);

	return 0;
}

int fetch_file(int sockfd, char *filename)
{
	char buffer[1024];
	bzero(buffer, 1024);
	write(sockfd, "OK", 2);
	read(sockfd, buffer, 1024);
	if(strcmp(buffer, "OK") != 0)
	{
		write(sockfd, "ABORT", 5);
		return -1;
	}
	char filepath[256];
	bzero(filepath, 256);
	strcpy(filepath, DSK);
	strcat(filepath, filename);
	
	FILE *fd = fopen(filepath, "r");
	print(filepath);
	if(fd != NULL)
	{
		write(sockfd, "EXIST", 5);
		
		bzero(buffer, 1024);
		read(sockfd, buffer, 1024);
		
		if(strcmp(buffer, "ABORT") == 0)
		{
			write(sockfd, "ABORT", 5);
			fclose(fd);
			return -1;
		}
	}
	
	
	fd = fopen(filepath, "w");
	
	if(fd == NULL)
	{
		write(sockfd, "ABORT", 5);
		return -1;
	}
	
	write(sockfd, "OK", 2);
	
	while(1)
	{
		bzero(buffer, 1024);
		read(sockfd, buffer, 1024);
		fwrite(buffer, sizeof(char), strlen(buffer), fd);
		if(strlen(buffer) < 1024)
			break;
	}
	
	fclose(fd);
	
	write(sockfd, "OK", 2);
			
	
	return 0;
}

int ls(int sockfd)
{
	int count = 0; 
	DIR *di;
	struct dirent *dir;
	di = opendir(DSK);
	char buffer[32];
	while ((dir = readdir(di)) != NULL) {
		write(sockfd, dir->d_name, strlen(dir->d_name));
		bzero(buffer, 32);
		read(sockfd, buffer, 32);
		if(strcmp("OK", buffer) != 0)
		{
			print("ERROR");
			break;
		}
		count++;
	}
	write(sockfd, "DONE", 4);
	bzero(buffer, 32);
	read(sockfd, buffer, 32);
	bzero(buffer, 32);
	sprintf(buffer, "%d files.", count);
	write(sockfd, buffer, strlen(buffer));
	return 0;
}

int fetch_files_with_ext(int sockfd, char *extension)
{
	write(sockfd, "OK", 2);
	char buffer[256];
	while(1)
	{
		bzero(buffer, 256);
		read(sockfd, buffer, 256);
		if(strcmp(buffer, "DONE") == 0)
			break;
		else fetch_file(sockfd, buffer);
	}
	write(sockfd, "OK", 2);
	return 0;
}

int send_files_with_ext(int sockfd, char *extension)
{
	char buffer[256];
	
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
			print(filename);
			write(sockfd, filename, strlen(filename));
			read(sockfd, buffer, 256);
			send_file(sockfd, filename);
			read(sockfd, buffer, 256);
			// break;
		}
	}
	
	write(sockfd, "DONE", 4);
	
	return 1;		
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
		read(clifd, buffer, 1000);
		print(buffer);
		if(strcmp("GET", buffer) == 0)
		{
			write(clifd, "OK", 2);
			bzero(buffer, 1000);
			read(clifd, buffer, 1000);
			send_file(clifd, buffer);
		}
		else if(strcmp("PUT", buffer) == 0)
		{
			write(clifd, "OK", 2);
			bzero(buffer, 1000);
			read(clifd, buffer, 1000);
			fetch_file(clifd, buffer);
		}
		else if(strcmp("MPUT", buffer) == 0)
		{
			write(clifd, "OK", 2);
			bzero(buffer, 1000);
			read(clifd, buffer, 1000);
			fetch_files_with_ext(clifd, buffer);
		}
		else if(strcmp("MGET", buffer) == 0)
		{
			write(clifd, "OK", 2);
			bzero(buffer, 1000);
			read(clifd, buffer, 1000);
			send_files_with_ext(clifd, buffer);
		}
		else if(strcmp("ls", buffer) == 0)
		{
			ls(clifd);
		}
		else {
			write(clifd, "ERROR", 5);
			continue;
		}
	}
	return 0;
}

/* Assumption
1. Read and write happens without error.
2. 
*/