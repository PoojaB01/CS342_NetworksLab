#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int connect_to_server(char *ip, char *port);
int send_file(char *filename);
int fetch_file(char *filename);
int send_files_with_ext(char *ext);
int fetch_files_with_ext(char *ext);
int ls();
int break_line(char *str, char *words[]);

