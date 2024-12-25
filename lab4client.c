#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<netdb.h>
#define SERV_TCP_PORT 5035
int main(int argc,char*argv[])
{
       int sockfd;
       struct sockaddr_in serv_addr;
       struct hostent*server;
       char buffer[4096];
       
           sockfd=socket(AF_INET,SOCK_STREAM,0);
           serv_addr.sin_family=AF_INET;
           serv_addr.sin_addr.s_addr=inet_addr("127.0.01");
           serv_addr.sin_port=htons(SERV_TCP_PORT);
           printf("\nReady for sending\n");
           connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
           fgets(buffer,4098,stdin);
           write(sockfd,buffer,4098);
       
       close(sockfd);
       return 0;
}