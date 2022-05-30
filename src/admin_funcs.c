#include "header.h"

/**
 *  Pannello di controllo admin
 */
void admin_control_panel(city_t *city_list) {
    int flag = 0;

    do {
        clear_terminal();
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
                clear_terminal();
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
                wrong_selection_message();
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

    clear_terminal();
    printf("\nInserisci il pin d'accesso amministratore: ");
    scanf("%d", &pin);
    getchar();

    if(pin == ADMIN_PIN) {
        return 1;
    } else {
        wrong_selection_message();
        return 0;
    }
}