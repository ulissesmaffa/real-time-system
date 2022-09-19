#include <pthread.h>
#include <stdio.h>
pthread_t tid1,tid2, tid3 ;

void * t0(){
     int i ;
     for (i=0; i<10; i++){
         printf("Eu sou a thread t0\n");
         sleep(1) ;
     }
  }
void * t1(){
     int i ;
     for (i=10; i<20; i++){
         printf("Eu sou a thread t1\n");
         sleep(1) ;
         }
    }
int main(){
   pthread_t tid1,tid2, tid3 ;
   printf("Eu sou a thread main\n");

  pthread_create(&tid1, NULL, t0, NULL);
  pthread_create(&tid2, NULL, t1, NULL);
  pthread_create(&tid3, NULL, t2, NULL);
  
  pthread_join(tid1, NULL);
  pthread_join(tid2 ,NULL);
  printf("Eu sou a thread main, t0 e t1 terminaram, vou terminar!!!!!\n");
  }

