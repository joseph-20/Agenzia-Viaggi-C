#include "header.h"

city_t *add_city_to_list(city_t *city_list, city_t *new) {
    if(city_list) {
        new->next = city_list;
    }
    return new;
}

int check_city(city_t *city_list, char city_name[]) {
    if(city_list) {
        while(city_list) {
            if(strcmp(city_list->name, city_name) == 0) {
                return 1;
            }
            city_list = city_list->next;
        }
    }
    return 0;
}

void free_city_matrix(city_t *city) {
    int i = 0;

    for(i = 0; i < city->npoi; i++) {
        free(city->poi[i]);
    }
    free(city->poi);
    city->poi = NULL;

    for(i = 0; i < city->npoi; i++) {
        free(city->poi_names[i]);
    }
    free(city->poi_names);
    city->poi_names = NULL;
}

city_t *new_city(char city_name[]) {
    city_t *new = (city_t *)malloc(sizeof(city_t));
    if(!new) {
        printf("\nErrore: impossibile allocare memoria.\n");
        return NULL;
    } else {
        strcpy(new->name, city_name);
        new->npoi = 0;
        new->poi = NULL;
        new->poi_names = NULL;
        new->next = NULL;
    }
    return new;
}

city_t *remove_city_from_list(city_t *city_list, char city_name[]) {
    city_t *tmp = NULL;
    if(!city_list) {
        return NULL;
    } else {
        if(strcmp(city_list->name, city_name) == 0) {
            tmp = city_list;
            city_list = city_list->next;
            free_city_matrix(tmp);
            free(tmp);
        } else {
            city_list->next = remove_city_from_list(city_list->next, city_name);
        }
        return city_list;
    }
}
