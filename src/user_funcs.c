#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

user_t *add_to_list(user_t *users_list, user_t *new) {
    if(users_list != NULL) {
        new->next = users_list;
    }
    return new;
}

int check_email(user_t *user_list, char email[]) {
    while(user_list) {
        if(strcmp(user_list->email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

int check_password(user_t *user_list, char email[], char password[]) {
    while(user_list) {
        if(strcmp(user_list->email, email) == 0) {
            if(strcmp(user_list->password, password) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

user_t *fetch_users(user_t *user_list) {
    char first_name[MAX_LONG],
        last_name[MAX_LONG],
        email[MAX_LONG],
        password[MAX_LONG],
        *token,
        line[LINE_MAX];
    FILE *users = NULL;
    user_t *new = NULL;

    users = fopen(USER_DB, "r");
    if(!users) {
        fputs("Impossibile aprire il database utenti.", stdout);
    } else {
        while(fgets(line, LINE_MAX, users) != NULL) {

            token = line;
            token = strtok(token, ",");
            strcpy(first_name, token);

            token = NULL;
            token = strtok(token, ",");
            strcpy(last_name, token);

            token = NULL;
            token = strtok(token, ",");
            strcpy(email, token);

            token = NULL;
            token = strtok(token, ",");
            strcpy(password, token);
            password[strlen(password) - 1] = 0;

            // printf("%s %s %s %s\n", first_name, last_name, email, password);

            new = new_user(first_name, last_name, email, password);
            user_list = add_to_list(user_list, new);
        }

        fclose(users);
    }
    return user_list;
}

user_t *get_user(user_t *user_list, char email[]) {
    if(user_list) {
        while(user_list) {
            if(strcmp(user_list->email, email) == 0) {
                return user_list;
            }
            user_list = user_list->next;
        }
    }
    return NULL;
}

user_t *sign_in(user_t *user_list) {
    char email[MAX_LONG],
        password[MAX_LONG];
    int flag = 0;
    user_t *user = NULL;

    do {
        printf("Inserisci email: ");
        scanf("%s", email);
        printf("Inserisci password: ");
        scanf("%s", password);

        if(check_email(user_list, email)) {
            if(!check_password(user_list, email, password)) {
                printf("Password errata.\n");
                flag = 1;
            }
        } else {
            printf("La email inserita non è corretta.\n");
            flag = 1;
        }
    } while(flag);

    user = get_user(user_list, email);
    return user;
}

user_t *sign_up(user_t *user_list) {
    char first_name[MAX_LONG],
        last_name[MAX_LONG],
        email[MAX_LONG],
        password[MAX_LONG];
    user_t *new = NULL;
    int flag = 0;

    printf("Inserisci nome: ");
    fgets(first_name, MAX_LONG, stdin);
    first_name[strlen(first_name) - 1] = 0;
    first_name[0] = toupper(first_name[0]);

    printf("Inserisci cognome: ");
    fgets(last_name, MAX_LONG, stdin);
    last_name[strlen(last_name) - 1] = 0;
    last_name[0] = toupper(last_name[0]);

    do {
        printf("Inserisci email: ");
        fgets(email, MAX_LONG, stdin);
        email[strlen(email) - 1] = 0;

        flag = check_email(user_list, email);
        if(flag) {
            printf("\nL'email inserita e' gia' in uso.\n");
        }
    } while(flag);


    printf("Inserisci password: ");
    fgets(password, MAX_LONG, stdin);
    password[strlen(password) - 1] = 0;

    new = new_user(first_name, last_name, email, password);
    user_list = add_to_list(user_list, new);

    update_user_list(user_list);

    return user_list;
}

user_t *new_user(char first_name[], char last_name[], char email[], char password[]) {
    user_t *new = (user_t *)malloc(sizeof(user_t));
    if(!new) {
        fputs("ERRORE: impossibile allocare memoria.", stdout);
        return NULL;
    } else {
        strcpy(new->first_name, first_name);
        strcpy(new->last_name, last_name);
        strcpy(new->email, email);
        strcpy(new->password, password);
        new->next = NULL;
        return new;
    }
}

void update_user_list(user_t *user_list) {
    FILE *users = fopen(USER_DB, "w+");
    while(user_list) {
        fprintf(users, "%s,%s,%s,%s\n", user_list->first_name, user_list->last_name, user_list->email, user_list->password);
        user_list = user_list->next;
    }
    fclose(users);
}