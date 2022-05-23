#ifndef HEADER_H
#define HEADER_H

#define MAX 20
#define MAX_LONG 50

typedef struct city {
    char name[MAX];                 // Nome della città
    int **poi;                      // Archi e Distanze dei Punti di Interesse
    char **poi_names;               // Nomi dei Punti di Interesse
} city_t;

typedef struct country {
    char name[MAX];                 // Nome del Paese
    int **cities;                   // Archi e Distanze tra le Città
    char **cities_names;            // Nome delle città
} country_t;

// Lista Single Linked per gli Utenti
typedef struct user {
    char first_name[MAX_LONG];      // Nome
    char last_name[MAX_LONG];       // Cognome
    char email[MAX_LONG];           // Email
    char password[MAX_LONG];        // Password
    struct user *next;
} user_t;

///////////////////////////////
//      Funzioni Utente      //
///////////////////////////////


///////////////////////////
//      Funzioni UI      //
///////////////////////////

void clear_screen();
#endif