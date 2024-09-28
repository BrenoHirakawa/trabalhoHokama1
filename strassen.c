#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "strassen.h"

int*** alocaMatriz(int NumMat, int arraySize){
    int ***matriz;

    matriz = malloc(NumMat * sizeof(int**));   

    for(int i = 0; i < NumMat; i++){
        matriz[i] = malloc(NumMat * sizeof(int*));
        for(int j = 0; j < NumMat; j++){
            matriz[i][j] = malloc(arraySize * sizeof(int));
        }
    }
        
    return matriz; 
}

void liberaMatriz(int*** matriz, int NumMat){
    for(int i = 0; i < NumMat; i++){
        for(int j = 0; i < NumMat; i++){
            free(matriz[i][j]); //Libera array
        }
        free(matriz[i]); // Libera linha
    }
    free(matriz);

}

void leMatriz(int*** matriz, int NumMat, int arraySize, int* valores){
    int index = 0; 

    for(int i = 0; i < NumMat; i++){
        for(int j = 0; j < NumMat; j++){
            for(int k = 0; k < arraySize; k++){
                matriz[i][j][k] = valores[index++];
            }
        }
    }

}

void imprimeMatriz(int*** matriz, int NumMat, int arraySize) {
    for (int i = 0; i < NumMat; i++) {
        for (int j = 0; j < NumMat; j++) {
            //printf("matriz[%d][%d]: ", i, j);
            for (int k = 0; k < arraySize; k++) {
                printf("%d ", matriz[i][j][k]);
            }
        }
        printf("\n");
    }
}

void divideMatriz(int*** matriz, int*** A, int*** B, int*** C, int*** D, int tam){
    // A, B, C e D são os quadrantes da matriz original
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            A[i][j] = matriz[i][j];              // Quadrante A
            B[i][j] = matriz[i][j + tam];        // Quadrante B
            C[i][j] = matriz[i + tam][j];        // Quadrante C
            D[i][j] = matriz[i + tam][j + tam];  // Quadrante D
        }
    }
}

void somaMatriz(){

}

void subMatriz(){

}

int strassen(int*** matriz1, int*** matriz2, int NumMat, int arraySize){

    int ***produto; 
    produto = malloc(NumMat * sizeof(int**));   

    for(int i = 0; i < NumMat; i++){
        produto[i] = malloc(NumMat * sizeof(int*));
        for(int j = 0; j < NumMat; j++){
            produto[i][j] = malloc(arraySize * sizeof(int));
        }
    }

    if (NumMat <= 2) {
        // Caso base: multiplicação de matrizes pequenas (2x2 ou 1x1)
        // Código para multiplicação direta
        return 0;
    }

    // Novo tamanho dos quadrantes
    int newSize = NumMat / 2;

    // Alocar espaço para os quadrantes
    //
    //  A   B   *   E   F   =   AE + BG     AF+BH
    //  C   D       G   H       CE + DG     CF+DH
    //
    int*** A = alocaMatriz(newSize, arraySize);
    int*** B = alocaMatriz(newSize, arraySize);
    int*** C = alocaMatriz(newSize, arraySize);
    int*** D = alocaMatriz(newSize, arraySize);
    int*** E = alocaMatriz(newSize, arraySize);
    int*** F = alocaMatriz(newSize, arraySize);
    int*** G = alocaMatriz(newSize, arraySize);
    int*** H = alocaMatriz(newSize, arraySize);
    

    int*** P1 = alocaMatriz(newSize, arraySize);
    int*** P2 = alocaMatriz(newSize, arraySize);
    int*** P3 = alocaMatriz(newSize, arraySize);
    int*** P4 = alocaMatriz(newSize, arraySize);
    int*** P5 = alocaMatriz(newSize, arraySize);
    int*** P6 = alocaMatriz(newSize, arraySize);
    int*** P7 = alocaMatriz(newSize, arraySize);

    int*** temp1 = alocaMatriz(newSize, arraySize); 
    int*** temp2 = alocaMatriz(newSize, arraySize); 


    //P1 = A*(F-H)
    subMatriz();
    subMatriz();
    strassen(temp1, temp2, NumMat, arraySize);

    //P2 = (A+B)
    subMatriz();
    subMatriz();
    strassen(temp1, temp2, NumMat, arraySize);


    liberaMatriz(A, newSize);
    liberaMatriz(B, newSize);
    liberaMatriz(C, newSize);
    liberaMatriz(D, newSize);
    liberaMatriz(E, newSize);
    liberaMatriz(F, newSize);
    liberaMatriz(G, newSize);
    liberaMatriz(H, newSize);

    liberaMatriz(P1, newSize);
    liberaMatriz(P2, newSize);
    liberaMatriz(P3, newSize);
    liberaMatriz(P4, newSize);
    liberaMatriz(P5, newSize);
    liberaMatriz(P6, newSize);
    liberaMatriz(P7, newSize);

}

