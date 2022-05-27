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
#define POI_DB "database/pois/"
#define ADMIN_PIN 0000

typedef struct city {
    char name[MAX_LONG];            // Nome della città
    int npoi;                       // # Punti di Interesse
    int **poi;                      // Archi e Distanze dei Punti di Interesse
    char **poi_names;               // Nomi dei Punti di Interesse
    struct city *next;
} city_t;

typedef struct country {
    char name[MAX];                 // Nome del Paese
    int ncities;                    // #Ccittà in un Paese
    int **cities;                   // Archi e Distanze tra le Città
    char **cities_names;            // Nome delle città
    struct country *next;
} country_t;

// Lista Single Linked per gli Utenti
typedef struct user {
    char first_name[MAX_LONG];      // Nome
    char last_name[MAX_LONG];       // Cognome
    char email[MAX_LONG];           // Email
    char password[MAX_LONG];        // Password
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
int check_city(city_t *city_list, char city_name[]);
city_t *fetch_cities();
void free_city_list(city_t *city_list);
void fetch_city_pois(city_t *city);
void free_city_matrix(city_t *city);
city_t *new_city(char city_name[], int npoi);
city_t *remove_city_from_list(city_t *city_list, char city_name[]);
void update_city_list(city_t *city_list);

//////////////////////////////
//      Funzioni Paese      //
//////////////////////////////

country_t *add_country_to_list(country_t *country_list, country_t *new);
void free_country_matrix(country_t *country);
country_t *new_country(char country_name[]);
country_t *remove_country_from_list(country_t *country_list, country_t *target);

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
int login_screen();

///////////////////////////////
//      Funzioni Utente      //
///////////////////////////////

user_t *add_user_to_list(user_t *users_list, user_t *new);
int check_email(user_t *user_list, char email[]);
int check_password(user_t *user_list, char email[], char password[]);
user_t *fetch_users();
void free_user_list(user_t *user_list);
user_t *get_user(user_t *user_list, char email[]);
user_t *sign_in(user_t *user_list);
user_t *sign_up(user_t *user_list);
user_t *new_user(char first_name[], char last_name[], char email[], char password[]);
void update_user_list(user_t *user_list);

#endif
