#include <stdio.h>
#include <time.h>    
#include <conio.h>   // Pentru _kbhit()
#include <windows.h> 
#include "joc.h"
#include "jucator.h"

// Cere o mutare de la jucator cu limita de timp
int cereMutareCuTimp(char simbol, int* linie, int* coloana) 
{
    int l = -1, c = -1;
    time_t start = time(NULL); // Momentul de start
    
    printf("Ai %d secunde sa introduci linia si coloana pentru %c (ex: 1 2): ", 
           LIMITA_TIMP, simbol);
    fflush(stdout);

    // Bucla care ruleaza pana cand expira timpul
    while (difftime(time(NULL), start) < LIMITA_TIMP) 
    {
        if (_kbhit()) 
        { // Verifica daca s-a apasat o tasta
            scanf("%d %d", &l, &c);
            l--; c--; // Convertesc din 1-3 la 0-2
            
            if (mutareValida(l, c)) 
            {
                *linie = l;
                *coloana = c;
                return 1; // Mutare valida
            } else 
            {
                printf("Pozitie invalida. Incearca din nou rapid: ");
                fflush(stdout);
            }
        }
        Sleep(100); // Pauza mica pentru a nu incarca CPU
    }
    
    printf("\nTimp expirat! Pierzi randul.\n");
    return 0; // Timpul a expirat
}

// Genereaza o mutare pentru calculator folosind o strategie simpla
void mutareCalculator(char simbol, int* linie, int* coloana) 
{
    char adversar = (simbol == 'X') ? 'O' : 'X';
    
    // 1. Verifica daca poate castiga la urmatoarea mutare
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            if (tabla[i][j] == ' ') 
            {
                tabla[i][j] = simbol;
                if (verificaCastigator(simbol)) 
                {
                    *linie = i;
                    *coloana = j;
                    printf("Calculatorul a ales pozitia %d %d\n", i+1, j+1);
                    return;
                }
                tabla[i][j] = ' ';
            }
        }
    }
    
    // 2. Verifica daca trebuie sa blocheze adversarul
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            if (tabla[i][j] == ' ') 
            {
                tabla[i][j] = adversar;
                if (verificaCastigator(adversar)) 
                {
                    tabla[i][j] = simbol;
                    *linie = i;
                    *coloana = j;
                    printf("Calculatorul a ales pozitia %d %d\n", i+1, j+1);
                    return;
                }
                tabla[i][j] = ' ';
            }
        }
    }
    
    // 3. Daca centrul este liber, il alege
    if (tabla[1][1] == ' ') 
    {
        *linie = 1;
        *coloana = 1;
        printf("Calculatorul a ales pozitia 2 2\n");
        return;
    }
    
    // 4. Alege un colt liber
    int colturi[4][2] = {{0,0}, {0,2}, {2,0}, {2,2}};
    for (int k = 0; k < 4; k++) 
    {
        int i = colturi[k][0];
        int j = colturi[k][1];
        if (tabla[i][j] == ' ') 
        {
            *linie = i;
            *coloana = j;
            printf("Calculatorul a ales pozitia %d %d\n", i+1, j+1);
            return;
        }
    }
    
    // 5. Alege orice pozitie libera ramasa
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            if (tabla[i][j] == ' ') 
            {
                *linie = i;
                *coloana = j;
                printf("Calculatorul a ales pozitia %d %d\n", i+1, j+1);
                return;
            }
        }
    }
}