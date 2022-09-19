#include <stdio.h>
#include <pthread.h>

    struct reg {
	  int a ;
	  int b[10][10];
    };

pthread_t tid1,tid2;
int soma0=0, soma1=0 ;

int m [10][10] ;

void * calculador0(struct reg *m0){
int i, j ;

  printf("Calculador0\n");
  for(i=0; i<5; i++) {
     for(j=0; j<10; j++) 
        {
          soma0 = soma0 + m0->b[i][j];
        }
     }
}

void * calculador1(struct reg * m1){
int i, j ;

  printf("Calculador1\n");
  for(i=5; i<10; i++) {
     for(j=0; j<10; j++) 
        {
          soma1 = soma1 + m1->b[i][j];
        }
     }
}


int main(){

  struct reg *m ;
  int result;
  int soma_total, i, j ;

  for(i=0; i<10; i++) {
     for(j=0; j<10; j++) 
        {
          m->b[i][j] = 1 ;
        }
     }

  printf("Eu sou o main\n");
  pthread_create(&tid1, NULL, calculador0, m);
  printf("Eu sou o main\n");
  result=pthread_create(&tid2, NULL, calculador1, m);
  printf("Eu sou o main\n");
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  soma_total = soma0 + soma1 ;
  printf("A soma total e: %d\n", soma_total);

}

