#include "header.h"

int main() {
    user_t *user_list = NULL,
        *user = NULL;
    country_t *country = NULL;
    int flag = 0;

    user_list = fetch_users();

    do {
        clear_screen();
        flag = main_menu();
        switch(flag) {
            case 1:
                user = sign_in(user_list);
                if(user != NULL) {
                    user_control_panel(user);
                    user = NULL;
                    update_user_list(user_list);
                }
                break;
            case 2:
                user_list = sign_up(user_list);
                break;
            case 3:
                if(login_admin()) {
                    // admin_control_panel(city_list);
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


    /*
     country = init_country();
     printf("%d\n", country->ncities);

     for(int i = 0; i < country->ncities; i++) {
         printf("%s\n", country->cities_names[i]);
     }

     printf("npoi: %d\n", country->city_list->npoi);

     for(int i = 0; i < country->city_list->npoi; i++) {
         for(int j = 0; j < country->city_list->npoi; j++) {
             printf("%-5d", country->city_list->poi[i][j]);
         }
         printf("\n");
     }

     for(int i = 0; i < country->city_list->npoi; i++) {
         printf("%s\n", country->city_list->poi_names[i]);
     }
    */


    free_user_list(user_list);
    user_list = NULL;
    /*
        free_city_list(city_list);
        city_list = NULL;
     */
    return 0;
}
