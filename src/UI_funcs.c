#include "header.h"

/**
 *  Funzione cross-platform per pulizia del terminale
 */
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 *  Funzione cross-platform di wait
 */
void csleep(int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
}

// Schermata di login
int main_menu() {
    int flag = 0;

    printf("1. Login");
    printf("\n2. Registrati");
    printf("\n3. Accesso Amministratore");
    printf("\n0. Esci");
    printf("\n> ");
    scanf("%d", &flag);
    getchar();

    return flag;
}
