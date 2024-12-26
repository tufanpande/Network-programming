#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#define CLI_TCP_PORT 5035
int main (int argc, char **argv)
{
int sockfd;
struct sockaddr_in serv_addr;
struct hostent * server;
sockfd=socket(AF_INET, SOCK_STREAM, 0) ;
serv_addr. sin_family=AF_INET;
serv_addr. sin_addr. s_addr=inet_addr("127.0.0.1");
serv_addr. sin_port=htons (CLI_TCP_PORT);
printf("\nReady for connect \n");
connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
close(sockfd);
return 0;
}