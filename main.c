//CTCO04 - Projeto e Análise de Algoritmos 
//Trabalho 01
//Breno Yukihiro Hirakawa - 2021001120
//Tiago Antonio Vilela Carvalho - 2022000969 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct array{
    int valores[3];
};

typedef struct array array;

array** alocaMatriz(int NumMat) {
    // Alocar a matriz de ponteiros para as linhas
    array** matriz = malloc(NumMat * sizeof(array*));
    for (int i = 0; i < NumMat; i++) {
        // Alocar cada linha da matriz de array
        matriz[i] = malloc(NumMat * sizeof(array));
    }
    return matriz;
}

void liberaMemoria(array** matriz, int NumMat){
    for (int i = 0; i < NumMat; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void imprimeMatriz(array** matriz, int NumMat) {
    for (int i = 0; i < NumMat; i++) {
        for (int j = 0; j < NumMat; j++) {
            printf("%d %d %d ", matriz[i][j].valores[0], matriz[i][j].valores[1], matriz[i][j].valores[2]);
        }
        printf("\n");
    }
}

array** somaMatriz(array** A, array** B, int NumMat) {
    array** resultado = alocaMatriz(NumMat);
    for (int i = 0; i < NumMat; i++) {
        for (int j = 0; j < NumMat; j++){
                resultado[i][j].valores[0] = A[i][j].valores[0] + B[i][j].valores[0];
                resultado[i][j].valores[1] = A[i][j].valores[1] + B[i][j].valores[1];
                resultado[i][j].valores[2] = A[i][j].valores[2] + B[i][j].valores[2];
        }
    }
    return resultado;
}

array** subtracaoMatriz(array** A, array** B, int NumMat) {
    array** resultado = alocaMatriz(NumMat);
    for (int i = 0; i < NumMat; i++) {
        for (int j = 0; j < NumMat; j++) {
            for (int k = 0; k < 3; k++) {
                resultado[i][j].valores[k] = A[i][j].valores[k] - B[i][j].valores[k];
            }
        }
    }
    return resultado;
}

void leMatriz(array** matriz, int NumMat) {
    for (int i = 0; i < NumMat; i++) {
        for (int j = 0; j < NumMat; j++) {
            for (int k = 0; k < 3; k++) {
                scanf("%d", &matriz[i][j].valores[k]);
            }
        }
    }
}

void divideMatriz(array** matriz, array** A11, array** A12, array** A21, array** A22, int newSize) {
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            for (int k = 0; k < 3; k++) {
                A11[i][j].valores[k] = matriz[i][j].valores[k];
                A12[i][j].valores[k] = matriz[i][j + newSize].valores[k];
                A21[i][j].valores[k] = matriz[i + newSize][j].valores[k];
                A22[i][j].valores[k] = matriz[i + newSize][j + newSize].valores[k];
            }
        }
    }
}

void combinaMatriz(array** C, array** C11, array** C12, array** C21, array** C22, int newSize) {
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            for (int k = 0; k < 3; k++) {
                C[i][j].valores[k] = C11[i][j].valores[k];
                C[i][j + newSize].valores[k] = C12[i][j].valores[k];
                C[i + newSize][j].valores[k] = C21[i][j].valores[k];
                C[i + newSize][j + newSize].valores[k] = C22[i][j].valores[k];
            }
        }
    }
}

array** multiplicaStrassen(array** matriz, array** matriz2, int  n){
    array** res = alocaMatriz(n);
    if (n <= 32) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < 3; k++) {
                    res[i][j].valores[k] = 0;  
                    for (int m = 0; m < n; m++) {  
                        res[i][j].valores[k] += matriz[i][m].valores[k] * matriz2[m][j].valores[k];
                    }
                }
            }
        }
        return res;
    }

    int newSize = n / 2;

    array** A = alocaMatriz(newSize);
    array** B = alocaMatriz(newSize);
    array** C = alocaMatriz(newSize);
    array** D = alocaMatriz(newSize);

    array** E = alocaMatriz(newSize);
    array** F = alocaMatriz(newSize);
    array** G = alocaMatriz(newSize);
    array** H = alocaMatriz(newSize);

    array** C11 = alocaMatriz(newSize);
    array** C12 = alocaMatriz(newSize);
    array** C21 = alocaMatriz(newSize);
    array** C22 = alocaMatriz(newSize);

    array** P1 = alocaMatriz(newSize);
    array** P2 = alocaMatriz(newSize);
    array** P3 = alocaMatriz(newSize); 
    array** P4 = alocaMatriz(newSize); 
    array** P5 = alocaMatriz(newSize); 
    array** P6 = alocaMatriz(newSize);
    array** P7 = alocaMatriz(newSize); 

    array** T1 = alocaMatriz(newSize);
    array** T2 = alocaMatriz(newSize);

    divideMatriz(matriz, A, B, C, D, newSize);
    divideMatriz(matriz2, E, F, G, H, newSize);

    // P1 = A * (F - H)
    T1 = subtracaoMatriz(F, H, newSize);
    P1 = multiplicaStrassen(A, T1, newSize);
    liberaMemoria(T1, newSize);

     // P2 = (A + B) * H
    T1 = somaMatriz(A, B, newSize);
    P2 = multiplicaStrassen(T1, H, newSize);
    liberaMemoria(T1, newSize);

    // P3 = (C + D) * E
    T1 = somaMatriz(C, D, newSize);
    P3 = multiplicaStrassen(T1, E, newSize);
    liberaMemoria(T1, newSize);

    // P4 = D * (G − E)
    T1 = subtracaoMatriz(G, E, newSize);
    P4 = multiplicaStrassen(D, T1, newSize);
    liberaMemoria(T1, newSize);

    // P5 = (A + D) * (E + H)
    T1 = somaMatriz(A, D, newSize);
    T2 = somaMatriz(E, H, newSize);
    P5 = multiplicaStrassen(T1, T2, newSize);
    liberaMemoria(T1, newSize);
    liberaMemoria(T2, newSize);

    // P6 = (B − D) * (G + H)
    T1 = subtracaoMatriz(B, D, newSize);
    T2 = somaMatriz(G, H, newSize);
    P6 = multiplicaStrassen(T1, T2, newSize);
    liberaMemoria(T1, newSize);
    liberaMemoria(T2, newSize);

    // P7 = (A − C) * (E + F)
    T1 = subtracaoMatriz(A, C, newSize);
    T2 = somaMatriz(E, F, newSize);
    P7 = multiplicaStrassen(T1, T2, newSize);
    liberaMemoria(T1, newSize);
    liberaMemoria(T2, newSize);


    // C11 = P5 + P4 - P2 + P6
    T1 = somaMatriz(P5, P4, newSize);
    T2 = subtracaoMatriz(T1, P2, newSize);
    C11 = somaMatriz(T2, P6, newSize);
    liberaMemoria(T1, newSize);
    liberaMemoria(T2, newSize);

    //C12 = P1 + P2
    C12 = somaMatriz(P1, P2, newSize);

    //C21 = P3 + P4
    C21 = somaMatriz(P3, P4, newSize);

    //C22 = P1 + P5 - P3 - P7
    T1 = somaMatriz(P1, P5, newSize);
    T2 = subtracaoMatriz(T1, P3, newSize);
    C22 = subtracaoMatriz(T2, P7, newSize);
    liberaMemoria(T1, newSize);
    liberaMemoria(T2, newSize);

    combinaMatriz(res, C11, C12, C21, C22, newSize);

    liberaMemoria(A, newSize);
    liberaMemoria(B, newSize);
    liberaMemoria(C, newSize);
    liberaMemoria(D, newSize);
    liberaMemoria(E, newSize);
    liberaMemoria(F, newSize);
    liberaMemoria(G, newSize);
    liberaMemoria(H, newSize);

    liberaMemoria(C11, newSize);
    liberaMemoria(C12, newSize);
    liberaMemoria(C21, newSize);
    liberaMemoria(C22, newSize);

    liberaMemoria(P1, newSize); 
    liberaMemoria(P2, newSize); 
    liberaMemoria(P3, newSize); 
    liberaMemoria(P4, newSize); 
    liberaMemoria(P5, newSize); 
    liberaMemoria(P6, newSize); 
    liberaMemoria(P7, newSize); 

    return res;
}


int main() {
    char tipo[3];
    int NumMat, max_val;

    scanf("%s", tipo); 
    scanf("%d %d", &NumMat, &NumMat);
    scanf("%d", &max_val);

    array** matriz = alocaMatriz(NumMat);
    array** matriz2 = alocaMatriz(NumMat);

    leMatriz(matriz, NumMat);
    leMatriz(matriz2, NumMat);

    array** resultado = multiplicaStrassen(matriz, matriz2, NumMat);

    printf("P3\n");
    printf("%d %d\n", NumMat, NumMat);
    printf("%d\n", max_val);
    imprimeMatriz(resultado, NumMat);

    // Liberar memória
    liberaMemoria(matriz, NumMat);
    liberaMemoria(matriz2, NumMat);
    liberaMemoria(resultado, NumMat); 
    
    return 0;
}



