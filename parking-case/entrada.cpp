#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define PORT 6325
#define IP_SERVER "172.17.0.2"

int main() {
    int s0,var;
    struct sockaddr_in server;
    
    //1:SOCKET
    s0=socket(AF_INET, SOCK_STREAM, 0);
        if (s0<0){
            perror("opening stream socket");
            exit(1);
        }
    //1:FIM SOCKET

    //2:CONEXAO COM SERVIDOR
    bzero(&server, sizeof(server)) ;
    server.sin_family = AF_INET ;
    server.sin_port = htons(PORT) ;
    server.sin_addr.s_addr = inet_addr(IP_SERVER);

    if (connect(s0, (struct sockaddr *) &server, sizeof(server))){
        perror("connectando stream socket");
        exit(0);
    }
    printf("ENTRADA: Conectado!\n");
    //2:FIM CONEXAO

    while(1){
        printf("ENTRADA: Digite 1 para ingressar no estacionamento:");
        scanf("%d",&var);
        if(var==1){
            send(s0,&var,sizeof(var),0);
        }else if(var==9){
            exit(1);
        }else{
            printf("ENTRADA: algo errado aconteceu!\n");
        }
    }

}