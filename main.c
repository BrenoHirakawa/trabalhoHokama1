#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strassen.h>


int main(){

    int P1,P2,P3,P4,P5,P6,P7;

    int NumMat = 0;

    printf("Escreva o valor da matriz: ");
    scanf("%d", &NumMat);

    printf("P3\n");
    printf("%d %d\n", NumMat, NumMat);
    matrizAleatoria(NumMat);


    return 0; 
}

