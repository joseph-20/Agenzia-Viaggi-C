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
            fetch_city_pois(new);
            city_list = add_city_to_list(city_list, new);
        }
        return city_list;
    }
}

void fetch_city_pois(city_t *city) {
    char file_name[MAX_LONG],
        trash;
    strcpy(file_name, POI_DB);
    strcat(strcat(file_name, city->name), ".txt");
    int i = 0,
        j = 0,
        tmp = 0;
    FILE *city_poi_db = fopen(file_name, "r");
    if(!city_poi_db) {
        printf("Impossibile recuperare i punti di interesse per %s.\n", city->name);
    } else {
        for(i = 0; i < city->npoi; i++) {
            for(j = 0; j < city->npoi; j++) {
                fscanf(city_poi_db, "%d", &city->poi[i][j]);
            }
        }

        fscanf(city_poi_db, "%c", &trash);

        for(i = 0; i < city->npoi; i++) {
            fgets(city->poi_names[i], MAX_LONG, city_poi_db);
            city->poi_names[i][strlen(city->poi_names[i]) - 1] = 0;
        }

        fclose(city_poi_db);
    }
}

void free_city_list(city_t *city_list) {
    city_t *tmp = NULL;

    while(city_list) {
        tmp = city_list;
        city_list = city_list->next;
        free_city_matrix(tmp);
        free(tmp);
    }
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
