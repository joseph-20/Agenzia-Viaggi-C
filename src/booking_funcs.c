#include "header.h"

void booking_main(user_t *user) {
    int flag = 0;
    do {
        switch(transport_choice()) {
            case 1:
                // Viaggio aereo
                break;
            case 2:
                // Viaggio treno
                break;
            case 0:
                break;
            default:
                wrong_selection_message();
                break;
        }
    } while(flag);
}

int transport_choice() {
    int choice = 0;

    do {
        clear_terminal();

        printf("Con quale mezzo desideri viaggiare?");
        printf("\n1. Aereo");
        printf("\n2. Treno");
        printf("\n0. Esci");
        printf("\n> ");

        scanf("%d", &choice);
        getchar();

        if(choice < 0 || choice > 2) {
            wrong_selection_message();
        }
    } while(choice < 0 || choice > 2);

    return choice;
}