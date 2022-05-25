#include "header.h"

// Check se void funziona
void insert_new_poi(city_t *city) {
    int i = 0;

    if(!city->poi) {
        city->poi = (int **)calloc(city->npoi, sizeof(int *));
        for(i = 0; i < city->npoi; i++) {
            city->poi[i] = (int *)calloc(city->poi, sizeof(int));
        }
    } else {
        city->poi = (int **)realloc(city->poi, city->npoi);
        for(i = 0; i < city->npoi; i++) {
            city->poi[i] = (int *)realloc(city->poi[i], city->poi);
        }
    }
}

// Check se void funziona
void insert_new_poi_name(city_t *city, char poi_name[]) {
    int i = 0;

    if(!city->poi_names) {
        city->poi_names = (char **)malloc(city->npoi * sizeof(char *));
        for(i = 0; i < MAX_LONG; i++) {
            city->poi_names[i] = (char *)malloc(MAX_LONG * sizeof(char));
        }
        strcpy(city->poi_names[city->npoi - 1], poi_name);
    } else {
        city->poi_names = (char **)realloc(city->poi_names, city->npoi);
        for(i = 0; i < city->npoi; i++) {
            city->poi_names[i] = (char *)realloc(city->poi_names[i], MAX_LONG);
        }
        strcpy(city->poi_names[city->npoi - 1], poi_name);
    }
}

void new_poi(city_t *city) {
    char name[MAX_LONG];

    if(city) {
        printf("\nInserisci il nome del nuovo punto di interesse: ");
        fgets(name, name, stdin);
        name[strcspn(name, "\n")] = 0;

        city->npoi += 1;
        insert_new_poi(city);
        insert_new_poi_name(city, name);
    }
}