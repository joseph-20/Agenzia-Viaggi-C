#include "header.h"

country_t *add_country_to_list(country_t *country_list, country_t *new) {
    if(country_list) {
        new->next = country_list;
    }
    return new;
}

void free_country_matrix(country_t *country) {
    int i = 0;

    for(i = 0; i < country->ncities; i++) {
        free(country->cities[i]);
    }
    free(country->cities);
    country->cities = NULL;

    for(i = 0; i < country->ncities; i++) {
        free(country->cities_names[i]);
    }
    free(country->cities_names);
    country->cities_names = NULL;
}

country_t *new_country(char country_name[]) {
    int i = 0;

    country_t *new = (country_t *)malloc(sizeof(country_t));
    if(!new) {
        printf("\nErrore: impossibile allocare la memoria.\n");
        return NULL;
    } else {
        strcpy(new->name, country_name);
        new->ncities = 0;
        new->cities = NULL;
        new->cities_names = NULL;
        new->next = NULL;
    }
    return new;
}

country_t *remove_country_from_list(country_t *country_list, country_t *target) {
    country_t *tmp = NULL;
    if(!country_list) {
        return NULL;
    } else {
        if(strcmp(country_list->name, target->name) == 0) {
            tmp = country_list;
            country_list = country_list->next;
            free_country_matrix(tmp);
            free(tmp);
        } else {
            country_list->next = remove_country_from_list(country_list->next, target);
        }
        return country_list;
    }
}
