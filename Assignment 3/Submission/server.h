#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int setup_server(char *port);
int send_file(int sockfd, char *filename);
int fetch_file(int sockfd, char *filename);
int send_files_with_ext(int sockfd, char *ext);
int fetch_files_with_ext(int sockfd, char *ext);
int break_line(char *str, char *words[]);
