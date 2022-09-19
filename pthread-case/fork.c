#include <stdio.h>

int main() {
int i, j, pid;

pid = -1 ;
pid = fork() ;
if (pid != 0) {
    printf("Eu sou o pai, e vou dormir!!\n") ;
    pid = wait (0) ; 
       
    i = getpid() ;
    printf("Eu sou o pai e acordei, meu pid e: %d \n", i) ;   
    printf(" O pid de meu filho e: %d\n", pid) ; 
    } 
else {
     for (i=0;i<5;i++){
       j = getpid() ; 
       printf("Eu sou o filho, meu pid e: %d \n", j );
       sleep (1) ; }
       j = getppid() ;
       printf("Eu sou o filho, o pid do meu pai e: %d \n", j );
     }
}
