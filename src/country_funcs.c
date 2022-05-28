#include "header.h"

/**
 *  Controllo se una città è già presente nella lista
 */
int check_city(country_t *country, char city_name[]) {
    for(int i = 0; i < country->ncities; i++) {
        if(strcmp(country->cities_names[i], city_name) == 0) {
            return 1;
        }
    }
    return 0;
}

char **create_char_matrix(int row, int length) {
    char **m = (char **)calloc(row, sizeof(char *));
    for(int i = 0; i < row; i++) {
        m[i] = (char *)calloc(length, sizeof(char));
    }

    return m;
}

int **create_int_matrix(int dim) {
    int **m = (int **)calloc(dim, sizeof(int *));
    for(int i = 0; i < dim; i++) {
        m[i] = (int *)calloc(dim, sizeof(int));
    }

    return m;
}

void free_country_matrix(country_t *country) {

}

country_t *init_country() {
    int i = 0;
    char trash;
    FILE *city_db = fopen(CITY_DB, "r");
    if(!city_db) {
        printf("Errore: database citta' non trovato.\n");
        return NULL;
    } else {
        country_t *new = new_country();
        if(!new) {
            printf("\nErrore: impossibile allocare la memoria.\n");
            return NULL;
        } else {
            fscanf(city_db, "%d", &new->ncities);

            new->city_costs_t = create_int_matrix(new->ncities);
            new->city_distances_t = create_int_matrix(new->ncities);
            new->city_costs_p = create_int_matrix(new->ncities);
            new->city_distances_p = create_int_matrix(new->ncities);
            new->cities_names = create_char_matrix(new->ncities, MAX_LONG);

            fscanf(city_db, "%c", &trash);

            for(i = 0; i < new->ncities; i++) {
                fgets(new->cities_names[i], MAX_LONG, city_db);
                new->cities_names[i][strcspn(new->cities_names[i], "\n")] = 0;
            }

            new->city_list = fetch_cities(city_db);
            if(!new->city_list) {
                printf("Errore: raccolta dettagli citta' non riuscita.\n");
                // free country matrix
                return NULL;
            }

            fclose(city_db);
            return new;
        }
    }
}

country_t *new_country() {
    country_t *new = (country_t *)malloc(sizeof(country_t));
    if(!new) {
        return NULL;
    } else {
        new->ncities = 0;
        new->city_costs_t = NULL;
        new->city_distances_t = NULL;
        new->city_costs_p = NULL;
        new->city_distances_p = NULL;
        new->cities_names = NULL;
        new->city_list = NULL;
        return new;
    }
}