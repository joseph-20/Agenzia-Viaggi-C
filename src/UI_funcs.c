#include "header.h"

// Pulizia del terminale
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait() {
    printf("Premi un tasto per continuare...\n");
    getchar();
}

// Schermata di login
int login_screen() {
    int flag = 0;

    printf("\n1. Login");
    printf("\n2. Registrati");
    printf("\n3. Accesso Amministratore");
    printf("\n0. Esci");
    printf("\n> ");
    scanf("%d", &flag);
    getchar();

    return flag;
}