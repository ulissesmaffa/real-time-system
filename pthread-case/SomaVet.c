#include <pthread.h>

pthread_t tid1,tid2,tid3;

int soma1, soma2, soma3;
int vet[3000];                         


void * t0(){

  int i=0;
  for(i=0;i<1000;i++) { 
     soma1 += vet[i];
     }
}


void * t1(){

  int i=0;
  for(i=1000;i<2000;i++) {
     soma2 += vet[i];
     }
}

void * t2(){

  int i=0;
  for(i=2000;i<3000;i++) {
     soma3 += vet[i];
     }
}   
         


int main(){

  int somatot,i;

  for(i=0;i<3000;i++) {
     if(i<1000)
       vet[i] = 1;
     else
     if(i<2000)
       vet[i] = 2;
     else
       vet[i] = 3;
  }  

  printf("MAIN\n");
 
  pthread_create(&tid1, NULL, t0, NULL);
  pthread_create(&tid2, NULL, t1, NULL);
  pthread_create(&tid3, NULL, t2, NULL);
  somatot = soma1 + soma2 + soma3;
  printf("Soma Total: %d\n",somatot);
}
