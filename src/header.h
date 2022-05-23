#ifndef HEADER_H
#define HEADER_H

#define MAX 20
#define MAX_LONG 50
#define LINE_MAX 150
#define USER_DB "database/users.txt"

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

user_t *add_to_list(user_t *users_list, user_t *new);
int check_email(user_t *user_list, char email[]);
int check_password(user_t *user_list, char email[], char password[]);
user_t *fetch_users(user_t *user_list);
user_t *get_user(user_t *user_list, char email[]);
user_t *sign_in(user_t *user_list);
user_t *sign_up(user_t *user_list);
user_t *new_user(char first_name[], char last_name[], char email[], char password[]);
void update_user_list(user_t *user_list);

///////////////////////////
//      Funzioni UI      //
///////////////////////////

void clear_screen();

#endif