#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define MAX 20
#define MAX_LONG 50
#define LINE_MAX 150
#define USER_DB "database/users.txt"
#define CITY_DB "database/city_list.txt"
#define ADMIN_PIN 0000

typedef struct city {
    int npoi;                       // # Punti di Interesse
    int **poi;                      // Distanze dei Punti di Interesse
    char **poi_names;               // Nomi dei Punti di Interesse
    struct city *next;
} city_t;

typedef struct country {
    int ncities;                    // # Città in un Paese
    int **city_costs_t;             // Costi di viaggio tra le Città in treno
    int **city_distances_t;         // Distanze tra le Città in treno
    int **city_costs_p;             // Costi di viaggio tra le città in aereo
    int **city_distances_p;         // Distanze tra le città in aereo
    char **cities_names;            // Nome delle città
    city_t *city_list;
} country_t;

// Lista Single Linked per gli Utenti
typedef struct user {
    char first_name[MAX_LONG];      // Nome
    char last_name[MAX_LONG];       // Cognome
    char email[MAX_LONG];           // Email
    char password[MAX_LONG];        // Password
    float balance;                  // Saldo Account
    struct user *next;
} user_t;

///////////////////////////////////////
//      Funzioni Amministratore      //
///////////////////////////////////////

void admin_control_panel(city_t *city_list);
void delete_city(city_t *city_list);
int login_admin();

//////////////////////////////
//      Funzioni Città      //
//////////////////////////////

city_t *add_city_to_list(city_t *city_list, city_t *new);
city_t *fetch_cities(FILE *city_db);
void free_city_list(city_t *city_list);
void free_city_matrix(city_t *city);
int get_city_index(country_t *country, char city_name[]);
city_t *new_city();
// remove city con realloc
void update_city_list(city_t *city_list);

//////////////////////////////
//      Funzioni Paese      //
//////////////////////////////

int check_city(country_t *country, char city_name[]);
char **create_char_matrix(int row, int length);
int **create_int_matrix(int dim);
void free_country_matrix(country_t *country);
country_t *init_country();
country_t *new_country();

///////////////////////////////////////////
//      Funzioni Punti di Interesse      //
///////////////////////////////////////////

void insert_new_poi(city_t *city);
void insert_new_poi_name(city_t *city, char poi_name[]);
void new_poi(city_t *city);

///////////////////////////
//      Funzioni UI      //
///////////////////////////

void clear_screen();
void csleep(int seconds);
int main_menu();

///////////////////////////////
//      Funzioni Utente      //
///////////////////////////////

user_t *add_user_to_list(user_t *users_list, user_t *new);
void balance_management(user_t *user);
void balance_top_up(user_t *user);
int check_email(user_t *user_list, char email[]);
int check_password(user_t *user_list, char email[], char password[]);
user_t *fetch_users();
void free_user_list(user_t *user_list);
user_t *get_user(user_t *user_list, char email[]);
user_t *sign_in(user_t *user_list);
user_t *sign_up(user_t *user_list);
user_t *new_user(char first_name[], char last_name[], char email[], char password[], float balance);
void update_user_list(user_t *user_list);
void user_control_panel(user_t *user);

#endif
