#include "header.h"

int main() {
    user_t *user_list = NULL,
        *user = NULL;

    country_t *country_list = NULL;
    city_t *city_list = NULL;
    int flag = 0;
    /*
        user_list = fetch_users();
        city_list = fetch_cities();

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
                        admin_control_panel(city_list);
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
     */

    city_list = fetch_cities();

    while(city_list) {
        printf("%s, %d\n", city_list->name, city_list->npoi);
        for(int i = 0; i < city_list->npoi; i++) {
            for(int j = 0; j < city_list->npoi; j++) {
                printf("%-5d", city_list->poi[i][j]);
            }
            printf("\n");
        }

        for(int i = 0; i < city_list->npoi; i++) {
            printf("%s\n", city_list->poi_names[i]);
        }

        printf("\n");
        city_list = city_list->next;
    }

    free_user_list(user_list);
    user_list = NULL;
    free_city_list(city_list);
    city_list = NULL;

    return 0;
}
