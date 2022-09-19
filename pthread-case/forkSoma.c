#include <stdio.h>
#include <signal.h>
#define N 1000

int main() {
  int A[N], B[N], somaA=0, somaB=0, i, j,l, x=50 ;
 
  for(i=0;i<N;i++) {
     A[i] = 1 ;
     B[i] = 2 ;
     }
  l = fork() ;
  if (l != 0) {
        printf("Eu vou somar o Vetor A\n") ;
        for (i=0; i<N; i++) {
            somaA = somaA + A[i] ;
            x++ ;
            }
       printf("Valor de x no pai: %d\n", x) ;
       printf("Soma do Vetor A: %d\n", somaA) ;
       printf("Variavel l no pai %d\n", l) ;
       sleep (5) ;
       kill (l, SIGKILL) ;
    } 
  else {
        printf("Sou o filho, vou dormir 3 segundo!!\n") ; 
        printf("PID do filho %d\n", getpid()) ;
	sleep (3) ;
	printf("Eu vou somar o Vetor B\n") ;
         for (i=0; i<N; i++){
            somaB = somaB + B[i] ;
            }
        printf("Soma do Vetor B: %d\n", somaB) ;
        printf("Valor de x no filho: %d\n", x) ;
        printf("Sou o filho, vou entrar em um loop eterno!!!\n") ;
        while(1) {}
       }
   
}
