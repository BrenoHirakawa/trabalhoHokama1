#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "strassen.h"

int*** alocaMatriz(int NumMat, int arraySize);

void liberaMatriz(int*** matriz, int NumMat);

void leMatriz(int*** matriz, int NumMat, int arraySize, int* valores);

void imprimeMatriz(int*** matriz, int NumMat, int arraySize);

void divideMatriz(int*** matriz, int*** A, int*** B, int*** C, int*** D, int tam);

int ***somaMatriz(int*** A, int*** B, int NumMat, int arraySize);

int ***subtracaoMatriz(int*** A, int*** B, int NumMat, int arraySize);

int ***strassen(int*** matriz1, int*** matriz2, int NumMat, int arraySize);


int main() {
    int NumMat = 4;  // Exemplo: matriz 4x4
    int arraySize = 3;  // Cada célula da matriz contém um array de 3 inteiros

    int*** matriz = alocaMatriz(NumMat, arraySize);
    int*** multiplo = alocaMatriz(NumMat, arraySize);
    int*** produto; //= alocaMatriz(NumMat, arraySize);


    // Valores de entrada (simulação da entrada que você forneceu)
    int valores1[] = {
        255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 255, 0,
        255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 255, 0,
        0, 0, 255, 0, 0, 255, 0, 255, 255, 0, 255, 255,
        0, 0, 255, 0, 0, 255, 0, 255, 255, 0, 255, 255
    };

    int valores2[]={
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };


    //produto = strassen(matriz, multiplo, NumMat, arraySize);


    // Lê os valores e preenche a matriz
    leMatriz(matriz, NumMat, arraySize, valores1);
    leMatriz(multiplo, NumMat, arraySize, valores2);

    // Imprime a matriz
    imprimeMatriz(matriz, NumMat, arraySize);
    imprimeMatriz(multiplo, NumMat, arraySize);

    produto = strassen(matriz, multiplo, NumMat, arraySize);
    printf("Produto\n");
    imprimeMatriz(produto, NumMat, arraySize);


    // Libera a memória alocada
    liberaMatriz(matriz, NumMat);
    liberaMatriz(multiplo, NumMat);
    liberaMatriz(produto, NumMat);

    return 0;
}

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


int ***somaMatriz(int*** A, int*** B, int NumMat, int arraySize){
    int ***res=  alocaMatriz(NumMat, arraySize);
    for(int i = 0; i < NumMat; i++){
        for(int j = 0; j < NumMat; j++){
            for(int k = 0; k < arraySize; k++){
                res[i][j][k] = A[i][j][k] + B[i][j][k];
            }
        }
    }
    return res; 
}

int ***subtracaoMatriz(int*** A, int*** B, int NumMat, int arraySize) {
    int ***res=  alocaMatriz(NumMat, arraySize);
    for (int i = 0; i < NumMat; i++) {
        for (int j = 0; j < NumMat; j++) {
            for (int k = 0; k < arraySize; k++) {
                res[i][j][k] = A[i][j][k] - B[i][j][k];
            }
        }
    }
    return res;
}

int ***strassen(int*** matriz1, int*** matriz2, int NumMat, int arraySize){

    int ***produto = alocaMatriz(NumMat,  arraySize);

    if (NumMat == 1) {
        for (int k = 0; k < arraySize; k++) {
            produto[0][0][k] = matriz1[0][0][k] * matriz2[0][0][k];  // Armazenar o produto em 'produto'
        }
        return produto;
    }

    int newSize = NumMat / 2;

    // Alocando quadrantes
    int*** A = alocaMatriz(newSize, arraySize);
    int*** B = alocaMatriz(newSize, arraySize);
    int*** C = alocaMatriz(newSize, arraySize);
    int*** D = alocaMatriz(newSize, arraySize);
    int*** E = alocaMatriz(newSize, arraySize);
    int*** F = alocaMatriz(newSize, arraySize);
    int*** G = alocaMatriz(newSize, arraySize);
    int*** H = alocaMatriz(newSize, arraySize);

    // Dividir matriz1 em quadrantes A, B, C, D e matriz2 em E, F, G, H
    divideMatriz(matriz1, A, B, C, D, newSize);
    divideMatriz(matriz2, E, F, G, H, newSize);

    // Alocando matrizes temporárias
    int*** P1 = alocaMatriz(newSize, arraySize);
    int*** P2 = alocaMatriz(newSize, arraySize);
    int*** P3 = alocaMatriz(newSize, arraySize);
    int*** P4 = alocaMatriz(newSize, arraySize);
    int*** P5 = alocaMatriz(newSize, arraySize);
    int*** P6 = alocaMatriz(newSize, arraySize);
    int*** P7 = alocaMatriz(newSize, arraySize);

    int*** temp1 = alocaMatriz(newSize, arraySize); 
    int*** temp2 = alocaMatriz(newSize, arraySize); 


    // P1 = A * (F - H)
    //temp1 = subtracaoMatriz(F, H, newSize, arraySize);
    P1 = strassen(A, subtracaoMatriz(F, H, newSize, arraySize), newSize, arraySize);

    // P2 = (A + B) * H
    temp1 = somaMatriz(A, B, newSize, arraySize);
    P2 = strassen(temp1, H, newSize, arraySize);

    // P3 = (C + D) * E
    temp1 = somaMatriz(C, D, newSize, arraySize);
    P3 = strassen(temp1, E, newSize, arraySize);

    // P4 = D * (G − E)
    temp1 = subtracaoMatriz(G, E, newSize, arraySize);
    P4 = strassen(D, temp1, newSize, arraySize);

    // P5 = (A + D) * (E + H)
    temp1 = somaMatriz(A, D, newSize, arraySize);
    temp2 = somaMatriz(E, H, newSize, arraySize);
    P5 = strassen(temp1, temp2, newSize, arraySize);

    // P6 = (B − D) * (G + H)
    temp1 = subtracaoMatriz(B, D, newSize, arraySize);
    temp2 = somaMatriz(G, H, newSize, arraySize);
    P6 = strassen(temp1, temp2, newSize, arraySize);

    // P7 = (A − C) * (E + F)
    temp1 = subtracaoMatriz(A, C, newSize, arraySize);
    temp2 = somaMatriz(E, F, newSize, arraySize);
    P7 = strassen(temp1, temp2, newSize, arraySize);

    // Recombinando os quadrantes
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            for (int k = 0; k < arraySize; k++) {
                produto[i][j][k] = P5[i][j][k] + P4[i][j][k] - P2[i][j][k] + P6[i][j][k];  // C11
                produto[i][j + newSize][k] = P1[i][j][k] + P2[i][j][k];                   // C12
                produto[i + newSize][j][k] = P3[i][j][k] + P4[i][j][k];                   // C21
                produto[i + newSize][j + newSize][k] = P5[i][j][k] + P1[i][j][k] - P3[i][j][k] - P7[i][j][k]; // C22
            }
        }
    }


    // Liberando a memória
    liberaMatriz(P1, newSize);
    liberaMatriz(P2, newSize);
    liberaMatriz(P3, newSize);
    liberaMatriz(P4, newSize);
    liberaMatriz(P5, newSize);
    liberaMatriz(P6, newSize);
    liberaMatriz(P7, newSize);
    liberaMatriz(temp1, newSize);
    liberaMatriz(temp2, newSize);


    return produto; 
}