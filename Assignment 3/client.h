// Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <dirent.h> 
#include <stdio.h>
#include <string.h>

// client disk location
#define DSK "./client_dir/"

// function prototypes
int connect_to_server(char *ip, char *port);
int send_file(int sockfd, char *filename);
int fetch_file(int sockfd, char *filename);
int send_files_with_ext(int sockfd, char *ext);
int fetch_files_with_ext(int sockfd, char *ext);
int break_line(char *str, char *words[]);
int ls(int sockfd);
void error(const char *msg);
void print(const char *msg);


