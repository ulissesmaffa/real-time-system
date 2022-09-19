#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define PORT 6325

//VARIAVEIS GLOBAIS
int sock, length,i,j,k,s0,s1,s2,status=0,lin,col;
struct sockaddr_in server,client;
char tab_jogadores[8][8], tab_jogo[8][8];

void imprime_tab_jogadores(){
    printf("Tabuleiro JOGADORES\n");
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            printf("%c ",tab_jogadores[i][j]);
        }
        printf("\n");
    }
}

void imprime_tab_jogo(){
    printf("\nTabuleiro JOGO\n");
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            printf("%c ",tab_jogo[i][j]);
        }
        printf("\n");
    }
}

void recv_solicitacao_jogo(){
    //Recebe solicitação de ingresso do jogo pelos clientes
    printf("\nServidor: vou responder a solicitacao de ingresso a todos!\n");

    recv(s0, &status, sizeof(status), 0);
    printf("Servidor: msg recebida do cliente %d para ingressar no jogo\n",status);
    
    recv(s1, &status, sizeof(status), 0);
    printf("Servidor: msg recebida do cliente %d para ingressar no jogo\n",status);
    
    recv(s2, &status, sizeof(status), 0);
    printf("Servidor: msg recebida do cliente %d para ingressar no jogo\n",status);
}

void send_tab_jogadores(){
    //envia o tabuleiro para todos os jogadores
    printf("\nServidor: vou enviar o tabuleiro a todos!\n");
             
    send(s0, &tab_jogadores, sizeof(tab_jogadores), 0);
    printf("Servidor: enviei tabuleiro ao cliente 0\n");
    
    send(s1, &tab_jogadores, sizeof(tab_jogadores), 0);
    printf("Servidor: enviei tabuleiro ao cliente 1\n");
    
    send(s2, &tab_jogadores, sizeof(tab_jogadores), 0);
    printf("Servidor: enviei tabuleiro ao cliente 2\n");
}

void envia_status(){
    //envia status para todos os jogadores
    printf("\nServidor: vou enviar status a todos, a vez de jogar eh do cliente:%d!\n",status);
             
    send(s0, &status, sizeof(status), 0);
    printf("Servidor: enviei status ao cliente 0\n");
    
    send(s1, &status, sizeof(status), 0);
    printf("Servidor: enviei status ao cliente 1\n");
    
    send(s2, &status, sizeof(status), 0);
    printf("Servidor: enviei status ao cliente 2\n");
    
}

void close(){
    close (s0);
    close (s1);
    close (s1);
}

void monta_tab_jogadores(){
    /*preenchimento tabuleiro JOGADORES*/
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            tab_jogadores[i][j]='a';
        }
    }
}

void monta_tab_jogo(){
    /*preenchimento tabuleiro JOGO*/
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(i==0&&j==1 || i==1&&j<2 || i==5&&j<4 || i==7&&j>=4&&j<=6){
                tab_jogo[i][j]='N';
            }else{
                tab_jogo[i][j]='a';
            }
        }
    }
    imprime_tab_jogo();
}

void recv_jogada(){
   //Recebe jogada do cliente da vez
    printf("\nServidor: vou receber a jogada de ataque do cliente %d!\n",status);

    switch (status)
    {
        case 0:
            recv(s0, &lin, sizeof(lin), 0);
            recv(s0, &col, sizeof(col), 0);
            printf("Servidor: o cliente %d jogou nas posicoes LxC:%dx%d\n",status,lin,col);
            break;
        case 1:
            recv(s1, &lin, sizeof(lin), 0);
            recv(s1, &col, sizeof(col), 0);
            printf("Servidor: o cliente %d jogou nas posicoes LxC:%dx%d\n",status,lin,col);   
            break;
        case 2:
            recv(s2, &lin, sizeof(lin), 0);
            recv(s2, &col, sizeof(col), 0);
            printf("Servidor: o cliente %d jogou nas posicoes LxC:%dx%d\n",status,lin,col);  
            break;
    
        default:
            printf("Algo estranho aconteceu ao receber a jogada de ataque!");
            break;
    }
}

void atualiza_tab_jogadores(){
    //atualiza tab_jogadores conforme a ultima jogada, dados de lin e col
    printf("Servidor: O ataque será realizado! LxC:%dx%d\n",lin,col);
    if(tab_jogo[lin][col]=='a'){
        tab_jogadores[lin][col]='X';
    }else if (tab_jogo[lin][col]=='N'){
        tab_jogadores[lin][col]='N';
    }else{
        printf("algo estranho aconteceu");
    }
}

int main() {
    //1:SOCKET
    sock = socket(AF_INET, SOCK_STREAM, 0); 
        if (sock < 0) {
            perror("opening stream socket");
            exit(0);
        }
    //FIM SOCKET

    //2:BIND
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons (PORT);
    length = sizeof (server);
        if (bind(sock, (struct sockaddr *)&server, length) < 0){
            perror("binding stream socket");
            exit(0);
        }
    //FIM BIND

    //3:LISTEN
    listen(sock,5);
    printf("Servidor: Aguardando conexao!\n");  
    //FIM LISTEN

    //4:ACCEPT;
    s0 = accept(sock,(struct sockaddr *)0,0);  
    s1 = accept(sock,(struct sockaddr *)0,0);  
    s2 = accept(sock,(struct sockaddr *)0,0);  
    printf("Servidor: Conexões estabelecidas!\n");  
    //FIM ACCEPT

    //INICIO DO JOGO
    //Preenchimento tabuleiros iniciais
    monta_tab_jogadores();
    monta_tab_jogo();

    //5: RECEBIMENTO DA SOLICITAÇÃO DE JOGO DOS CLIENTES
    recv_solicitacao_jogo();
    //6: CONFIRMAÇÃO DA SOLICITACÃO COM ENVIO DO TABULEIRO JOGADORES
    send_tab_jogadores();

    /*
    7: LOOP DO JOGO
    7.1 => envia status a todos, que vem a ser a "vez de jogar";
    7.2 => recebe jogada lin x col do jogador da vez e vazio dos demais;
    7.3 => atualiza tabuleiro jogadores conforme a jogada realizada;
    */
    status=0;
    while(k!=24){
        envia_status();
        recv_jogada();
        atualiza_tab_jogadores();
        send_tab_jogadores();
        
        //atualizacao do status
        status++;
        if (status==3){
            status=0;
        }
        
        k++;
    }

    close();
}
