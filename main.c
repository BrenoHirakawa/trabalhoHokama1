#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "strassen.h"

int main() {
    int NumMat = 4;  // Exemplo: matriz 4x4
    int arraySize = 3;  // Cada célula da matriz contém um array de 3 inteiros

    // Valores de entrada (simulação da entrada que você forneceu)
    int valores[] = {
        255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 255, 0,
        255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 255, 0,
        0, 0, 255, 0, 0, 255, 0, 255, 255, 0, 255, 255,
        0, 0, 255, 0, 0, 255, 0, 255, 255, 0, 255, 255
    };

    int mult[]={
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    // Aloca a matriz 4x4
    int*** matriz = alocaMatriz(NumMat, arraySize);
    int*** multiplo = alocaMatriz(NumMat, arraySize);

    // Lê os valores e preenche a matriz
    leMatriz(matriz, NumMat, arraySize, valores);
    leMatriz(multiplo, NumMat, arraySize, mult);

    // Imprime a matriz
    imprimeMatriz(matriz, NumMat, arraySize);
    imprimeMatriz(multiplo, NumMat, arraySize);

    // Libera a memória alocada
    liberaMatriz(matriz, NumMat);
    liberaMatriz(multiplo, NumMat);

    return 0;
}