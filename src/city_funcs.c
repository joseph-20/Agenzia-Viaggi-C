#include "header.h"

/**
 *  Aggiunta di una nuova città alla lista
 */
city_t *add_city_to_list(city_t *city_list, city_t *new) {
    if(city_list) {
        new->next = city_list;
    }
    return new;
}

/**
 *  Controllo se una città è già presente nella lista
 */
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

/**
 *  Fetch delle città e dei loro punti di interesse dal file/database
 */
city_t *fetch_cities() {
    char city_name[MAX_LONG],
        line[LINE_MAX],
        *token;
    int city_npoi;
    FILE *cities = NULL;
    city_t *city_list = NULL,
        *new = NULL;

    cities = fopen(CITY_DB, "r");
    if(!cities) {
        fputs("Impossibile aprire il database delle citta'.", stdout);
        return NULL;
    } else {
        while(fgets(line, LINE_MAX, cities) != NULL) {
            token = line;
            token = strtok(token, ",");
            strcpy(city_name, token);

            token = NULL;
            token = strtok(token, ",");
            city_npoi = atoi(token);

            new = new_city(city_name, city_npoi);
            fetch_city_pois(new, cities);
            city_list = add_city_to_list(city_list, new);
        }
        return city_list;
    }
}

/**
 *  Fetch dei punti di interesse
 */
void fetch_city_pois(city_t *city, FILE *city_list) {
    char trash;
    int i = 0,
        j = 0,
        tmp = 0;

    for(i = 0; i < city->npoi; i++) {
        for(j = 0; j < city->npoi; j++) {
            fscanf(city_list, "%d", &city->poi[i][j]);
        }
    }

    fscanf(city_list, "%c", &trash);

    for(i = 0; i < city->npoi; i++) {
        fgets(city->poi_names[i], MAX_LONG, city_list);
        city->poi_names[i][strcspn(city->poi_names[i], "\n")] = 0;
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
city_t *new_city(char city_name[], int npoi) {
    int i = 0;
    city_t *new = (city_t *)malloc(sizeof(city_t));
    if(!new) {
        printf("\nErrore: impossibile allocare memoria.\n");
        return NULL;
    } else {
        strcpy(new->name, city_name);

        new->npoi = npoi;
        new->poi = (int **)calloc(npoi, sizeof(int *));
        for(i = 0; i < npoi; i++) {
            new->poi[i] = (int *)calloc(npoi, sizeof(int));
        }

        new->poi_names = (char **)malloc(npoi * sizeof(char *));
        for(i = 0; i < npoi; i++) {
            new->poi_names[i] = (char *)malloc(MAX_LONG * sizeof(char));
        }

        new->next = NULL;
    }
    return new;
}

/**
 *  Cancellazione di una città dalla lista
 */
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

/**
 * Ristampa la lista nel file/database
 */
void update_city_list(city_t *city_list) {
    FILE *cities = fopen(CITY_DB, "w");
    if(!cities) {
        fputs("Impossibile aggiornare il database citta'.", stdout);
    } else {
        while(city_list) {
            fprintf(cities, "%s,%d\n", city_list->name, city_list->npoi);
            city_list = city_list->next;
        }
        fclose(cities);
    }
}
