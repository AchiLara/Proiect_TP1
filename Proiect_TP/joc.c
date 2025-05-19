#include <stdio.h>
#include <windows.h>  // Pentru functia Sleep
#include "joc.h"

char tabla[N][N]; // Tabla de joc

// Initializeaza tabla cu spatii libere
void initializeazaTabla() 
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tabla[i][j] = ' ';
}

// Afiseaza tabla de joc cu linii de separare
void afiseazaTabla() 
{
    printf("\n   ");
    for (int j = 0; j < N; j++) 
        printf("%d   ", j + 1); // Afiseaza numarul coloanei
    printf("\n");
    
    for (int i = 0; i < N; i++) 
    {
        printf("%d ", i + 1); // Afiseaza numarul liniei
        for (int j = 0; j < N; j++) 
        {
            printf(" %c ", tabla[i][j]); 
            if (j < N-1) printf("|"); 
        }
        printf("\n");
        if (i < N-1) 
        {
            printf("  ---+---+---\n"); 
        }
    }
    printf("\n");
}

int verificaCastigator(char simbol) 
{
    // Verifica linii
    for (int i = 0; i < N; i++) 
    {
        if (tabla[i][0] == simbol && tabla[i][1] == simbol && tabla[i][2] == simbol) 
            return 1;
    }
    
    // Verifica coloane
    for (int j = 0; j < N; j++) 
    {
        if (tabla[0][j] == simbol && tabla[1][j] == simbol && tabla[2][j] == simbol) 
            return 1;
    }
    
    // Verifica diagonale
    if (tabla[0][0] == simbol && tabla[1][1] == simbol && tabla[2][2] == simbol) 
        return 1;
    if (tabla[0][2] == simbol && tabla[1][1] == simbol && tabla[2][0] == simbol) 
        return 1;
    
    return 0;
}

// Verifica daca tabla este plina 
int esteRemiza() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (tabla[i][j] == ' ') 
                return 0;
    return 1;
}

// Verifica daca o mutare este valida
int mutareValida(int linie, int coloana) 
{
    return (linie >= 0 && linie < N && 
            coloana >= 0 && coloana < N && 
            tabla[linie][coloana] == ' ');
}

// Plaseaza un simbol pe tabla
void seteazaMutare(int linie, int coloana, char simbol) 
{
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