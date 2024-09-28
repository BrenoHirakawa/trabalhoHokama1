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
        for(int j = 0; j < NumMat; j++){
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

void somaMatriz(int*** A, int*** B, int*** resultado, int NumMat, int arraySize){
    for(int i = 0; i < NumMat; i++){
        for(int j = 0; j < NumMat; j++){
            for(int k = 0; k < arraySize; k++){
                resultado[i][j][k] = A[i][j][k] + B[i][j][k];
            }
        }
    }
}

void subtracaoMatriz(int*** A, int*** B, int*** resultado, int NumMat, int arraySize) {
    for (int i = 0; i < NumMat; i++) {
        for (int j = 0; j < NumMat; j++) {
            for (int k = 0; k < arraySize; k++) {
                resultado[i][j][k] = A[i][j][k] - B[i][j][k];
            }
        }
    }
}


void strassen(int*** matriz1, int*** matriz2, int NumMat, int arraySize){

    int ***produto; 
    produto = malloc(NumMat * sizeof(int**));   

    for(int i = 0; i < NumMat; i++){
        produto[i] = malloc(NumMat * sizeof(int*));
        for(int j = 0; j < NumMat; j++){
            produto[i][j] = malloc(arraySize * sizeof(int));
        }
    }

    // if (NumMat <= 2) {
    //     // Caso base: multiplicação de matrizes pequenas (2x2 ou 1x1)
    //     // Código para multiplicação direta
    //     return 1;
    // }

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

    divideMatriz(matriz1, A, B, C, D, newSize);
    divideMatriz(matriz2, E, F, G, H, newSize);

    int*** P1 = alocaMatriz(newSize, arraySize);
    int*** P2 = alocaMatriz(newSize, arraySize);
    int*** P3 = alocaMatriz(newSize, arraySize);
    int*** P4 = alocaMatriz(newSize, arraySize);
    int*** P5 = alocaMatriz(newSize, arraySize);
    int*** P6 = alocaMatriz(newSize, arraySize);
    int*** P7 = alocaMatriz(newSize, arraySize);

    int*** temp1 = alocaMatriz(newSize, arraySize); 
    int*** temp2 = alocaMatriz(newSize, arraySize); 


    //P1 = A*(F - H)
    subtracaoMatriz(F, H, temp1, NumMat, arraySize);
    strassen(temp1, A, newSize, arraySize);

    //P2 = (A + B)*H
    somaMatriz(A, B, temp1, NumMat, arraySize);
    strassen(temp1, H, newSize, arraySize);

    //P3 = (C + D)*E
    somaMatriz(C, D, temp1, NumMat, arraySize);
    strassen(temp1, E, newSize, arraySize);

    //P4 = D*(G − E)
    subtracaoMatriz(G, E, temp1, NumMat, arraySize);
    strassen(temp1, D, newSize, arraySize);

    //P5 = (A + D)*(E + H)
    somaMatriz(A, D, temp1, NumMat, arraySize);
    somaMatriz(E, H, temp2, NumMat, arraySize);
    strassen(temp1, temp2, newSize, arraySize);

    //P6 = (B − D)*(G + H) 
    subtracaoMatriz(B, D, temp1, NumMat, arraySize);
    somaMatriz(G, H, temp2, newSize, arraySize);
    strassen(temp1, temp2, newSize, arraySize);

    //P7 = (A − C)*(E + F)
    subtracaoMatriz(A, C, temp1, NumMat, arraySize);
    somaMatriz(E, F, temp1, newSize, arraySize);
    strassen(temp1, temp2, newSize, arraySize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            for (int k = 0; k < arraySize; k++) {
                // C11
                produto[i][j][k] = P5[i][j][k] + P4[i][j][k] - P2[i][j][k] + P6[i][j][k];
                // C12
                produto[i][j + newSize][k] = P1[i][j][k] + P2[i][j][k];
                // C21
                produto[i + newSize][j][k] = P3[i][j][k] + P4[i][j][k];
                // C22
                produto[i + newSize][j + newSize][k] = P5[i][j][k] + P1[i][j][k] - P3[i][j][k] - P7[i][j][k];
            }
        }
    }


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

