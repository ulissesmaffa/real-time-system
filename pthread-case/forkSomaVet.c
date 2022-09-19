#include <stdio.h>

int p[2] ;

int main() {
  int A[100], B[100], somaA=0, somaB=0, somaTotal, i, j, pid;
  pipe(p) ;
  for(i=0;i<100;i++) {
     A[i] = 1 ;
     B[i] = 2 ;
     }
  pid = fork() ;
  if (pid != 0) {
        printf("Eu vou somar o Vetor A\n") ;
        for (i=0; i<100; i++) {
            somaA = somaA + A[i] ;
            }
       printf("Soma doVetor A: %d\n", somaA) ;
       printf("Vou esperar pela soma de B\n");
       read(p[0],&somaB , sizeof(int)) ;
       somaTotal = somaA + somaB ;
       printf("Soma Total: %d \n", somaTotal) ;
    } 
  else {
         printf("Eu vou somar o Vetor B\n") ;
         for (i=0; i<100; i++){
            somaB = somaB + B[i] ;
            }
        printf("Soma do Vetor B: %d\n", somaB) ;
        write(p[1],&somaB, sizeof(int)) ;
        printf("Escrevi no pipe a soma do vetor  B\n");
       }
   
}
