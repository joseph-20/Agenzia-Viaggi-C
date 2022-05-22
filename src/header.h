#ifndef HEADER_H
#define HEADER_H

#define LEN 20

typedef struct city {
    char name[LEN];         // Nome della città
    int **poi;              // Archi e Distanze dei Punti di Interesse
    char **poi_names;       // Nomi dei Punti di Interesse
} city_t;

typedef struct country {
    char name[LEN];         // Nome del Paese
    int **cities;           // Archi e Distanze tra le Città
    char **cities_names;    // Nome delle città
} country_t;

#endif