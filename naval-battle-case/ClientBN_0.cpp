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

#define IP_SERVER "10.34.58.79"

int main() {
    int s0,i,j,k,status,lin,col;
    struct sockaddr_in server;
    char tab_jogadores[8][8];

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
    printf("Cliente 0: Conectado!\n");
    //2:FIM CONEXAO

    //3:SEND INICIAL
    //Solicitação para ingresso no jogo
    status=0;
    send(s0, &status, sizeof(status), 0);
    printf("Cliente 0: Solicitação para ingresso em batalha naval enviada!\n");

    //4:RECV INICIAL
    //Confirmação de ingresso no jogo através do envio do tabuleiro pelo servidor
    recv(s0, &tab_jogadores, sizeof(tab_jogadores), 0);
    printf("Servidor: Sua solicitação foi atendida, segue o tabuleiro do jogo!\n");
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            printf("%c ",tab_jogadores[i][j]);
        }
        printf("\n");
    }

    /*
    5:LOOP DO JOGO
    5.1 => recebe status do servidor
    5.2 => verifica se eh sua vez de jogar | envia jogada se for vez de jogar ou fica aguardando
    5.3 => recebe tabuleiro atualizado do servidor
    */

    while(k!=24){
        recv(s0, &status, sizeof(status), 0);//5.1
        printf("Servidor: status enviado eh:%d\n",status);
        if(status==0){//5.2
            printf("eh sua vez de jogar!\n");
            printf("DIGITE LINHA E COLUNA QUE DESEJA ATACAR!\n");
            scanf("%d %d",&lin,&col);
            send(s0, &lin, sizeof(lin), 0);
            send(s0, &col, sizeof(col), 0);
            printf("Cliente 0: ataque LxC:%dx%d enviado para servidor!\n",lin,col);
        }else{
            printf("aguarde sua vez! o cliente %d esta realizando sua jogada\n",status);
        }

        recv(s0, &tab_jogadores, sizeof(tab_jogadores), 0);//5.3
        printf("\nServidor: Tabuleiro atualizado apos o ataque do cliente: %d!\n",status);
        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                printf("%c ",tab_jogadores[i][j]);
            }
            printf("\n");
        }

        k++;
    }

    //FIM DA CONEXAO
    printf("\nCliente 0: FORAM 24 TENTATIVAS AO TOTAL, FIM DE JOGO!\n");
    close (s0);
}