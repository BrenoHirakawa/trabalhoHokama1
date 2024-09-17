#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrizAleatoria(int NumMat);

int** alocaMatriz(int NumMat){
    int **matriz, i;

    matriz = malloc(NumMat * sizeof(int*));   

    for(i = 0; i < NumMat; i++)
        matriz[i] = malloc(NumMat * sizeof(int));

    return matriz; 
}

void liberaMatriz(int** matriz, int NumMat){
    for(int i = 0; i < NumMat; i++)
        free(matriz[i]); // Liberando cada linha
    free(matriz);

}

void matrizAleatoria(int NumMat){

    int **matriz = alocaMatriz(NumMat);
    

    for(int i = 0; i < NumMat; i++){
        for(int j = 0; j < NumMat; j++){
            matriz[i][j] = rand() % 255;
        }
    }

    for(int i = 0; i < NumMat; i++){
        for(int j = 0; j < NumMat; j++){
            printf("%d  ",matriz[i][j]);
        }
        printf("\n");
    }

    liberaMatriz(matriz, NumMat);

}

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

