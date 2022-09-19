#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int main()
{
long t;
int i,j,pesq,tam,tmili;
int vet[100000],vet_res[100000];
struct timeval inicio, final;

srand((unsigned) time(&t));//auxilia a funcao random a ficar mais random
tam=100000;

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

//algoritmo de procura
j=0;
for (i=0;i<=tam;i++){
  if(vet[i] == pesq){
    vet_res[j]= i;
    j++;
  }
}

printf("\nO numero: %d aparece: %d vezes no vetor, as posicao sao:",pesq,j);
for (i=0;i<j;i++){
  printf(" %d -",vet_res[i]);
}
printf("\n\n");

//termina de contar o tempo de execucao
gettimeofday(&final, NULL);
tmili = (int)(1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec)/1000);
printf("\nTempo decorrido: %d \n", tmili);

}
