#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>//DECLARAR PTHREAD
#include <semaphore.h>//USAR SEMAFAROS - PARA USAR O J COMAPRTILHADO

//varias globais
int vet[10],vet_res[10];
int i,j=0,pesq,tam;
sem_t s0;

//CRIAR FUNCOES DAS PTHREAD PARA FUNCIONAR EM PARARELO
void * t0(){
  for (i=0;i<=tam/2;i++){
    if(vet[i] == pesq){
      sem_wait(&s0);//consultando o semafaro, se for 1 passa se for 0 fica parado - coloca zero
      vet_res[j]= i;
      j++;
      sem_post(&s0);//coloca 1 no semaforo
    }
  }
}

void * t1(){
  for (i=tam/2;i<=tam;i++){
    if(vet[i] == pesq){
      sem_wait(&s0);
      vet_res[j]= i;
      j++;
      sem_post(&s0);
    }
  }
}

int main(){

  long t;
  int tmili;
  struct timeval inicio, final;
  //DECLARAR VARIAL DA PTHREAD
  pthread_t tid1,tid2;

  sem_init(&s0,0,1);//1 quer dizer aberto

  srand((unsigned) time(&t));//auxilia a funcao random a ficar mais random

  tam=10;

  gettimeofday(&inicio, NULL);//começa a contar o tempo de execucao

  //preecnimento do vetor random
  for (i=0;i<=tam;i++){
    vet[i] = rand() % 9;
  }
  //impressao do vetor incial
  for (i=0;i<=tam;i++){
    printf("\nvetor[%d]: %d",i,vet[i]);
  }
  printf("\nDigite o valor que deseja pesquisar:\n");
  scanf("%d",&pesq);

  //algoritmo de procura - divide a procura nas duas thread
  pthread_create(&tid1, NULL, t0, NULL);
  pthread_create(&tid2, NULL, t1, NULL);
  pthread_join(tid1, NULL);//se nao coloca isso o main termina antes e acaba com as threads
  pthread_join(tid2, NULL);

  //impressao do vetor resultado
  printf("\nO numero: %d aparece: %d vezes no vetor, as posicoes sao:",pesq,j);
  for (i=0;i<j;i++){
    printf(" %d -",vet_res[i]);
  }
  printf("\n\n");

  //termina de contar o tempo de execucao
  gettimeofday(&final, NULL);
  tmili = (int)(1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec)/1000);
  printf("\nTempo decorrido: %d \n", tmili);

}
