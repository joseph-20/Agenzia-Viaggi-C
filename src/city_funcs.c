#include "header.h"

/**
 *  Aggiunta di una nuova città in coda alla lista (ricorsiva)
 */
city_t *add_city_to_list(city_t *city_list, city_t *new) {
    if(!city_list) {
        return new;
    } else {
        city_list->next = add_city_to_list(city_list->next, new);
        return city_list;
    }
}

/**
 *  Fetch delle città e dei loro punti di interesse dal file/database
 */
city_t *fetch_cities(FILE *city_db) {
    int i = 0,
        j = 0,
        tmp = 0;
    char trash;
    city_t *city_list = NULL,
        *new = NULL;

    new = new_city();
    if(!new) {
        printf("Errore: impossibile allocare citta'.\n");
        return NULL;
    } else {
        fscanf(city_db, "%d", &new->npoi);

        fscanf(city_db, "%c", &trash);

        new->poi = create_int_matrix(new->npoi);
        new->poi_names = create_char_matrix(new->npoi, MAX_LONG);

        for(i = 0; i < new->npoi; i++) {
            for(j = 0; j < new->npoi; j++) {
                fscanf(city_db, "%d", &new->poi[i][j]);
            }
        }

        fscanf(city_db, "%c", &trash);

        for(i = 0; i < new->npoi; i++) {
            fgets(new->poi_names[i], MAX_LONG, city_db);
            new->poi_names[i][strcspn(new->poi_names[i], "\n")] = 0;
        }

        city_list = add_city_to_list(city_list, new);

        return city_list;
    }
}

/**
 *  Deallocazione della lista delle città
 */
void free_city_list(city_t *city_list) {
    city_t *tmp = NULL;

    while(city_list) {
        tmp = city_list;
        city_list = city_list->next;
        free_city_matrix(tmp);
        free(tmp);
    }
}

/**
 *  Deallocazione delle matrici di ogni nodo città
 */
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

/**
 *  Allocazione di un nodo città
 */
city_t *new_city() {
    int i = 0;
    city_t *new = (city_t *)malloc(sizeof(city_t));
    if(!new) {
        printf("\nErrore: impossibile allocare memoria.\n");
        return NULL;
    } else {
        new->npoi = 0;
        new->poi = NULL;
        new->poi_names = NULL;
        new->next = NULL;
    }
    return new;
}

/**
 *  Cancellazione di una città dalla lista
 */
city_t *remove_city_from_list(country_t *country, int index) {

}

int get_city_index(country_t *country, char city_name[]) {
    int i = 0;
    while(strcmp(country->cities_names[i], city_name) != 0) {
        i++;
    }
    return i;
}

/**
 * Ristampa la lista nel file/database
 */
void update_city_list(city_t *city_list) {
    int i = 0,
        j = 0;
    FILE *cities = fopen(CITY_DB, "w");
    if(!cities) {
        fputs("Impossibile trovare e/o aggiornare il database citta'.", stdout);
    } else {
        while(city_list) {
            fprintf(cities, "%d\n", city_list->npoi);

            for(i = 0; i < city_list->npoi; i++) {
                for(j = 0; j < city_list->npoi - 1; j++) {
                    fprintf(cities, "%d ", city_list->poi[i][j]);
                }
                fprintf(cities, "%d\n", city_list->poi[i][j]);
            }

            for(i = 0; i < city_list->npoi; i++) {
                fprintf(cities, "%s\n", city_list->poi_names[i]);
            }

            city_list = city_list->next;
        }
        fclose(cities);
    }
}
