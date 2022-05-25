#include "header.h"

city_t *add_city_to_list(city_t *city_list, city_t *new) {
    if(city_list) {
        new->next = city_list;
    }
    return new;
}

void free_city_matrix(city_t *city) {
    int i = 0;

    for(i = 0; i < city->npoi; i++) {
        free(city.poi[i]);
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
        new->npo = 0;
        new->poi = NULL;
        new->poi_names = NULL;
        new->next = NULL;
    }
    return new;
}