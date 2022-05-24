#include "header.h"

// Fase di login amministratore
int login_admin() {
    int pin = 0;

    clear_screen();
    printf("\nInserisci il pin d'accesso amministratore: ");
    scanf("%d", &pin);
    getchar();

    if(pin == ADMIN_PIN) {
        return 1;
    } else {
        printf("\n-------------------------");
        printf("\n|    Password Errata    |");
        printf("\n-------------------------\n");
        csleep(3);
        return 0;
    }
}