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
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

#define PORT 6325
#define VAGA 3

//VARIAVEIS GLOBAIS SOCKET
int sock,length,s0,s1;
struct sockaddr_in server,client;

int n,vaga[VAGA],id_ticket=0,arrecadacao=0;
pthread_t ent,sai,tcarro[100];
sem_t sem_ent,sem_sai,sem_arrecada;

int defineTempo(){
    int t;
    t=rand()%10;
    return t;
}

void iniciaVagas(){
    int i;
    for(i=0;i<VAGA;i++){
        //vagas abertas=1
        vaga[i]=1;
    }
}

int vagasDisponiveis(){
    int i,qtd=0;
    for(i=0;i<VAGA;i++){
        //deixa as vagas abertas
        if(vaga[i]==1){
            qtd++;
        }
    }
    return qtd;
}

int escolheVaga(){
    int i;
    for(i=0;i<VAGA;i++){
        if(vaga[i]==1){
            return i;
        }
    }
}

void insereArrecada(int v){
    sem_wait(&sem_arrecada);
    arrecadacao=arrecadacao+v;
    sem_post(&sem_arrecada);
}

void imprimeArrecada(){
    printf("\n\nARRECADAÇÃO:%d\n\n",arrecadacao);
}


void *carro(void *id_carro){
    // id=(int *)id_carro;
    printf("id_carro:%d\n",id_carro);
    int vagas_disponiveis,ticket_local,vaga_escolhida,tempo;
    printf("Carro%d: iniciada\n",id_carro);
    
    sem_wait(&sem_ent);
        //verifica disponibilidade de vaga
        vagas_disponiveis=vagasDisponiveis();
        if(vagas_disponiveis>0){
            printf("CARRO:%d O estacionamento tem %d vagas disponiveis\n",id_carro,vagas_disponiveis);
            //gera número de ticket
            ticket_local=id_ticket+1;
            //insere na lista ticket
            //funcao para inserir na lista
            printf("CARRO:%d Ticket %d gerado com sucesso!\n",id_carro,ticket_local);
            //escolhe vaga
            vaga_escolhida=escolheVaga();
            printf("CARRO:%d Vaga %d com sucesso!\n",id_carro,vaga_escolhida);
            //define-se tempo
            tempo=defineTempo();
            printf("CARRO:%d Tempo de %d segundos definido com sucesso!\n",id_carro,tempo);
            //preenche vaga
            vaga[vaga_escolhida]=0;
        }else{
            printf("No momento não há vagas disponíveis, vá embora Carro %d!\n",id_carro);
        }
    sem_post(&sem_ent);
    //aguarda tempo na vaga
    sleep(tempo);
    //valida ticket
    insereArrecada(10);
    //solicita saida

    //liberar saída
    send(s1,&id_carro,sizeof(id_carro),0);
    sem_wait(&sem_sai);
        //libera vaga
        vaga[vaga_escolhida]=1;
    sem_post(&sem_sai);
}

void *entrada(void *n){
    int carro_id=1,recv_ent=0;
    printf("ENTRADA: iniciada\n");
    while(1){
        recv(s0, &recv_ent, sizeof(recv_ent), 0);
        printf("ENTRADA: solicitação de entrada! carro_id:%d\n",carro_id);
            pthread_create(&tcarro[carro_id], NULL, carro, (int *) (carro_id));
            carro_id++;
    }

}

void *saida(void *n){
    printf("SAIDA: iniciada\n");
    // send(s1,&send_sai,sizeof(send_sai),0);

}

int main(){
    int var;
    srand( (unsigned)time(NULL));
    sem_init(&sem_ent,0,1);
    sem_init(&sem_sai,0,1);
    sem_init(&sem_arrecada,0,1);
    iniciaVagas();

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
    printf("SERVER: Aguardando conexao!\n");  
    //FIM LISTEN

    //4:ACCEPT;
    s0 = accept(sock,(struct sockaddr *)0,0);  
    s1 = accept(sock,(struct sockaddr *)0,0);  
    printf("SERVER: Conexões estabelecidas!\n");  
    //FIM ACCEPT

    printf("SERVER: iniciando estacionamento\n");
    pthread_create(&ent,NULL,entrada,(int *) &n);
    pthread_create(&sai,NULL,saida,(int *) &n);

    while(1){
        printf("RELATÓRIOS: 1=ARRECADAÇÃO:\n");
        scanf("%d",&var);
        switch (var)
        {
        case 1:
            imprimeArrecada();
            break;
        
        default:
            break;
        }
    }

    pthread_join(ent,NULL);
    pthread_join(sai,NULL);
}
