#include "header.h"

int main() {
    user_t *user_list = NULL,
        *user = NULL;

    country_t *country_list = NULL;
    city_t *Napoli = NULL;
    int flag = 0;

    user_list = fetch_users(user_list);

    do {
        clear_screen();
        flag = login_screen();
        switch(flag) {
            case 1:
                user = sign_in(user_list);
                // Panoramica account e store
                user = NULL;
                break;
            case 2:
                user_list = sign_up(user_list);
                break;
            case 3:
                if(login_admin()) {
                    // Pannello controllo admin
                }
                break;
            case 0:
                break;
            default:
                clear_screen();
                printf("\nInserisci un'opzione valida.\n");
                csleep(3);
                break;
        }
    } while(flag);

    free_user_list(user_list);
    user_list = NULL;

    return 0;
}