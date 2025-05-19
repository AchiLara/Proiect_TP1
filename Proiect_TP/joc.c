#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "joc.h"

char tabla[N][N]; // Tabla globala de dimensiune NxN

// Initializeaza tabla cu spatii libere
void initializeazaTabla() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tabla[i][j] = ' ';
}

// Afiseaza tabla de joc cu linii de separare
void afiseazaTabla() {
    printf("\n   ");
    for (int j = 0; j < N; j++) {
        printf(" %2d ", j + 1); // Afiseaza numarul coloanei
    }
    printf("\n");
    
    // Corpul tablei
    for (int i = 0; i < N; i++) {
        // Linia cu simboluri
        printf("%2d ", i + 1); // Numerotare randuri cu 2 cifre
        for (int j = 0; j < N; j++) {
            printf(" %c ", tabla[i][j]);
            if (j < N - 1) printf("|");
        }
        printf("\n");
        
        // Linia de separare (doar intre randuri)
        if (i < N - 1) {
            printf("   ");
            for (int j = 0; j < N; j++) {
                printf("---");
                if (j < N - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

int verificaCastigator(char simbol) {
    int castiga_linie, castiga_coloana;
    
    // Verifica linii si coloane
    for (int i = 0; i < N; i++) {
        castiga_linie = 1;
        castiga_coloana = 1;
        for (int j = 0; j < N; j++) {
            if (tabla[i][j] != simbol) castiga_linie = 0;
            if (tabla[j][i] != simbol) castiga_coloana = 0;
        }
        if (castiga_linie || castiga_coloana) return 1;
    }
    
    // Verifica diagonale
    int castiga_diag1 = 1, castiga_diag2 = 1;
    for (int i = 0; i < N; i++) {
        if (tabla[i][i] != simbol) castiga_diag1 = 0;
        if (tabla[i][N-1-i] != simbol) castiga_diag2 = 0;
    }
    
    return castiga_diag1 || castiga_diag2;
}

int esteRemiza() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (tabla[i][j] == ' ') return 0;
    return 1;
}

int mutareValida(int linie, int coloana) {
    return (linie >= 0 && linie < N && 
            coloana >= 0 && coloana < N && 
            tabla[linie][coloana] == ' ');
}

void seteazaMutare(int linie, int coloana, char simbol) {
    tabla[linie][coloana] = simbol;
}

// Afiseaza animatie pentru castigator
void animatieCastigator(char castigator)
 {
     printf("\n\n");
    for (int i = 0; i < 3; ++i) 
    {
        printf("  Felicitari %c! Ai castigat jocul! \n", castigator);
        Sleep(1000);  // 1000 ms = 1s (Windows)
    }
}
