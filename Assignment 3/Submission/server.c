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
		print("file opened.");
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

int mput(int sockfd, char *s)
{
    DIR *di;
    char *filename;  //will store the filename
    char *extension;  //will store the file extension
    struct dirent *sample_dir;
    int flag;
    if(strcmp(s, "txt")==0)
    {
      flag= 0;
    }
    else if(strcmp(s,"c")==0)
    {
      flag= 1;
    }
    else 
    {
      printf("Incorrect extension\n");
      return -1;
    }
    di = opendir("."); //specify the Client disk directory path here
    if (di) //check if directory exists or not. if it exists, continue
    {
        while ((sample_dir = readdir(di)) != NULL) //read all files inside Client directory in this   manner
        {
            filename=strtok(sample_dir->d_name,".");
            extension=strtok(NULL,".");
            if(extension!=NULL)
            {
            	 if(flag==0) //When flag is set to zero, it means .txt file
            	 {
            	  int check; //this check flag will help in matching the extension of file with required
            	  check =strcmp(extension,"txt");
                  if(check==0)
                  {
                    printf("Transferring text file %s\n",filename);
                  }
                  /*
                  Call the PUTS functions here for this file
                  */
                  
            	 }
            	 else if(flag==1) //When flag is set to one, it means .c file
            	 {
  
            	   int check; //this check flag will help in matching the extension of file with required
            	   check =strcmp(extension,"c");
                  if(check==0)
                  {
                    printf("Transferring C file %s\n",filename);
                  }
                  /*
                  Call the PUTS function here for this file
                  */
                  
            	 }
               
            }
            
        }
      
        closedir(di); //Close the directory now
        printf("FInished transferring all necessary files \n");
        return 0;
    }
    else 
    {
    	//If di is NULL, that means there was an error opening the client directory
    	printf("Error opening directory");
    	return -1;
    }
}

int mget(int sockfd, char *s)
{
    DIR *di;
    char *filename;  //will store the filename
    char *extension;  //will store the file extension
    struct dirent *sample_dir;
    int flag;
    if(strcmp(s, "txt")==0)
    {
      flag=0;
    }
    else if(strcmp(s, "c")==0)
    {
      flag=1;
    }
    else 
    {
      printf("Incorrect Extension\n");
      return -1;
    }
    di = opendir("."); //specify the Server disk directory path here
    if (di) //check if directory exists or not. if it exists, continue
    {
        while ((sample_dir = readdir(di)) != NULL) //read all files inside Server directory in this   manner
        {
            filename=strtok(sample_dir->d_name,".");
            extension=strtok(NULL,".");
            if(extension!=NULL)
            {
            	 if(flag==0) //When flag is set to zero, it means .txt file
            	 {
            	  int check; //this check flag will help in matching the extension of file with required
            	  check =strcmp(extension,"txt");
                  if(check==0)
                  {
                    printf("Fetching text file %s\n",filename);
                  }
                  /*
                  Call the GETS functions here for this file
                  */
                  
            	 }
            	 else if(flag==1) //When flag is set to one, it means .c file
            	 {
  
            	   int check; //this check flag will help in matching the extension of file with required
            	   check =strcmp(extension,"c");
                  if(check==0)
                  {
                    printf("Fetching C file %s\n",filename);
                  }
                  /*
                  Call the GETS function here for this file
                  */
            	 }
               
            }
            
        }
        closedir(di); //Close the directory now
        printf("FInished fetching all necessary files\n");
        return 0;
    }
    else 
    {
    	//If di is NULL, that means there was an error opening the client directory
    	printf("Error opening directory");
    	return -1;
    }
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
		else if(strcmp("MGET", buffer) == 0)
		{
			write(clifd, "OK", 2);
			bzero(buffer, 1000);
			read(clifd, buffer, 1000);
			write(clifd, "I will send a files.", 20);
		}
		else if(strcmp("MPUT", buffer) == 0)
		{
			write(clifd, "OK", 2);
			bzero(buffer, 1000);
			read(clifd, buffer, 1000);
			write(clifd, "I will fetch a files.", 21);
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
