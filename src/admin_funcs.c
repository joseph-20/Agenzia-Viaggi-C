#include "header.h"

/**
 *  Pannello di controllo admin
 */
void admin_control_panel(city_t *city_list) {
    int flag = 0;

    do {
        clear_screen();
        printf("\nCosa si desidera fare?");
        printf("\n1. Aggiungi collegamento");
        printf("\n2. Rimuovi meta");
        printf("\n0. Esci");
        printf("\n> ");
        scanf("%d", &flag);
        getchar();

        switch(flag) {
            case 1:
                // Aggiungi arco
                break;
            case 2:
                clear_screen();
                // Rivedere
                /*
                delete_city(city_list);
                update_city_list(city_list);
                */
                csleep(3);
                break;
            case 0:
                break;
            default:
                printf("\nInserire un'opzione valida.\n");
                csleep(3);
                break;
        }
    } while(flag);
}

/**
 *  Cancellazione di una meta
 */
void delete_city(city_t *city_list) {

}

/**
 *  Controllo login amministratore
 */
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