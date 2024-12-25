//write a program to implement forkclint and forkserver
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

#define SERV_TCP_PORT 5035
int main (int argc, char **argv)
{
int i, sockfd, newsockfd;
socklen_t clength;
struct sockaddr_in serv_addr,cli_addr;
char buffer [4098];
pid_t childpid;

sockfd=socket(AF_INET, SOCK_STREAM, 0) ;

serv_addr. sin_family=AF_INET;
serv_addr. sin_addr. s_addr=INADDR_ANY;
serv_addr. sin_port=htons (SERV_TCP_PORT);
printf("\n start");

bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr));

listen(sockfd,5);
printf("\n Listening.......");

i=1;
for(;;)
{
    
listen(sockfd,5);
clength= sizeof(cli_addr);
newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clength);
printf("\nAccepted.");
if((childpid=fork())==0)
{
    printf("\n Child PID is: %d",getpid());
    read(newsockfd, buffer,4096);
    printf("\nClient Message: %s",buffer);
}
close(newsockfd);
i++;
}
return 0;
}