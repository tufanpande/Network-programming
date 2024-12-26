#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#define SERV_TCP_PORT 5035
int main (int argc, char **argv)
{
int sockfd, newsockfd,clength;
struct sockaddr_in serv_addr,cli_addr;
sockfd=socket(AF_INET, SOCK_STREAM, 0) ;
serv_addr. sin_family=AF_INET;
serv_addr. sin_addr. s_addr=INADDR_ANY;
serv_addr. sin_port=htons (SERV_TCP_PORT);
printf("\n start");
bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr));
printf("\n Listening.......");
listen(sockfd,1);
clength= sizeof(cli_addr);
newsockfd= accept(sockfd, (struct sockaddr *)&cli_addr,&clength);
printf("\nAccepted\n");
close(sockfd);
}   