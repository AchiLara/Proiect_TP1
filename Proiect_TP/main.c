#include <stdio.h>
#include <string.h>
#include "retea.h"
#include "joc.h"
#include "jucator.h"

int main() {
    int optiune;
    printf("Alege modul de joc:\n");
    printf("1 - Joc in retea (2 jucatori)\n");
    printf("2 - Joc contra calculatorului\n");
    printf("Optiunea ta: ");
    scanf("%d", &optiune);

    initializeazaTabla();
    

    if (optiune == 1) 
    {
        // Joc in retea intre 2 jucatori
        int esteServer;
        char ip[100], port[10];
        int socketJoc;

        printf("Esti server (1) sau client (0)? ");
        scanf("%d", &esteServer);

        if (esteServer) 
        {
            printf("Introdu portul pentru conexiune: ");
            scanf("%s", port);
            socketJoc = pornesteServer(port);
            if (socketJoc == -1) 
            {
                printf("Eroare la pornirea serverului!\n");
                return 1;
            }
        } else 
        {
            printf("Introdu IP-ul serverului: ");
            scanf("%s", ip);
            printf("Introdu portul: ");
            scanf("%s", port);
            socketJoc = conecteazaLaServer(ip, port);
            if (socketJoc == -1) 
            {
                printf("Eroare la conectarea la server!\n");
                return 1;
            }
        }

        int randul = 0;
        char simboluri[2] = {'X', 'O'};

        while (1) 
        {
            int linie, coloana;
            printf("\n--- Randul jucatorului %c ---\n", simboluri[randul]);

            if ((esteServer && randul == 0) || (!esteServer && randul == 1)) 
            {
                // Randul jucatorului local
                if (cereMutareCuTimp(simboluri[randul], &linie, &coloana)) 
                {
                    seteazaMutare(linie, coloana, simboluri[randul]);
                    if (!trimiteMutare(socketJoc, linie, coloana)) 
                    {
                        printf("Eroare la trimiterea mutarii!\n");
                        break;
                    }
                } else 
                {
                    printf("Mutare ratata, trece randul.\n");
                    trimiteMutare(socketJoc, -1, -1);
                }
            } 
            else 
            {
                // Randul adversarului
                printf("Asteapta mutarea adversarului...\n");
                if (!primesteMutare(socketJoc, &linie, &coloana)) 
                {
                    printf("Conexiunea s-a pierdut!\n");
                    break;
                }
                if (linie != -1 && coloana != -1) 
                {
                    seteazaMutare(linie, coloana, simboluri[randul]);
                } else 
                {
                    printf("Adversarul a pierdut randul.\n");
                }
            }

            afiseazaTabla();

            // Verifica castigator
            if (verificaCastigator(simboluri[randul])) 
            {
                animatieCastigator(simboluri[randul]);
                break;
            }

            // Verifica remiza
            if (esteRemiza()) 
            {
                printf("\nRemiza! Niciun jucator nu a castigat.\n");
                break;
            }

            randul = 1 - randul; // Schimba jucatorul
        }

        inchideSocket(socketJoc);
    } else 
    {
        // Joc impotriva calculatorului
        int randul = 0;
        char simboluri[2] = {'X', 'O'}; // 'X' este jucatorul, 'O' este calculatorul

        while (1) {
            int linie, coloana;
            printf("\n--- Randul jucatorului %c ---\n", simboluri[randul]);

            if (randul == 0) { // Randul jucatorului 
                if (!cereMutareCuTimp(simboluri[randul], &linie, &coloana)) 
                {
                    printf("Rand pierdut!\n");
                    randul = 1;
                    continue;
                }
            } else { // Randul calculatorului
                mutareCalculator(simboluri[randul], &linie, &coloana);
            }

            seteazaMutare(linie, coloana, simboluri[randul]);
            afiseazaTabla();

            // Verifica castigator
            if (verificaCastigator(simboluri[randul])) 
            {
                animatieCastigator(simboluri[randul]);
                break;
            }

            // Verifica remiza
            if (esteRemiza()) 
            {
                printf("\nRemiza! Niciun jucator nu a castigat.\n");
                break;
            }

            randul = 1 - randul; // Schimba jucatorul
        }
    }

    return 0;
}