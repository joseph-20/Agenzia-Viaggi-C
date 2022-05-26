#include "header.h"

// Pulizia del terminale
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void csleep(int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
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
