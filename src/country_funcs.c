#include "header.h"
/*
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
        new->city_distances_t = NULL;
        new->city_costs_t = NULL;
        new->cities_names = NULL;
    }
    return new;
}
 */