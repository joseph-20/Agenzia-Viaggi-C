#include "header.h"

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
                delete_city(city_list);
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

void delete_city(city_t *city_list) {
    char name[MAX];
    printf("\nInserisci il nome della citta' da eliminare: ");
    fgets(name, MAX, stdin);
    name[strcspn(name, "\n")] = 0;

    if(check_city(city_list, name)) {
        remove_city_from_list(city_list, name);
        printf("\nCitta' eliminata con successo.\n");
    } else {
        printf("\nLa citta' specificata non esiste.\n");
    }
}

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