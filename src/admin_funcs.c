#include "header.h"

/**
 *  Pannello di controllo admin
 */
void admin_control_panel(country_t *country) {
    int flag = 0,
        reports = 0;
    int **reports_matrix = NULL;

    reports = fetch_reports();

    do {
        clear_terminal();

        if(reports == -1) {
            printf("+----------------------------------------+\n");
            printf("|    Impossibile recuperare i reports    |\n");
            printf("+----------------------------------------+\n");
        } else if(reports) {

            reports_matrix = create_reports(reports);

            if(reports == 1) {
                printf("+---------------------------+\n");
                printf("|    Hai 1 nuovo report!    |\n");
                printf("+---------------------------+\n");
            } else {
                printf("+----------------------------+\n");
                printf("|    Hai %-2d nuovi report!    |\n", reports);
                printf("+----------------------------+\n");
            }
        }

        printf("\nCosa si desidera fare?");
        printf("\n1. Aggiungi collegamento");
        printf("\n2. Rimuovi meta");
        printf("\n0. Esci");
        printf("\n> ");
        scanf("%d", &flag);
        getchar();

        switch(flag) {
            case 1:
                // Aggiungi arco
                break;
            case 2:
                clear_terminal();
                remove_city(country);
                // Aggiornamento database
                csleep(DEFAULT_SLEEP);
                break;
            case 0:
                break;
            default:
                wrong_selection_message();
                break;
        }
    } while(flag);

    for(int i = 0; i < reports; i++) {
        free(reports_matrix[i]);
    }
    free(reports_matrix);
}

int **create_reports(int dim) {
    FILE *reports = fopen(REPORTS_DB, "r");

    int **mat = (int **)calloc(dim, sizeof(int *));
    for(int i = 0; i < dim; i++) {
        mat[i] = (int *)calloc(2, sizeof(int));
    }

    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < 2; j++) {
            fscanf(reports, "%d", &mat[i][j]);
        }
    }

    return mat;
}

int fetch_reports() {
    int reports_amount = 0;
    char buffer;
    FILE *reports = fopen(REPORTS_DB, "r");
    if(!reports) {
        return -1;
    } else {
        while(!feof(reports)) {
            buffer = fgetc(reports);
            if(buffer == '\n') {
                reports_amount++;
            }
        }

        return reports_amount;
    }
}

/**
 *  Controllo login amministratore
 */
int login_admin() {
    int pin = 0;

    clear_terminal();
    printf("Inserisci il pin d'accesso amministratore: ");
    scanf("%d", &pin);
    getchar();

    if(pin == ADMIN_PIN) {
        return 1;
    } else {
        clear_terminal();
        printf("+------------------------+\n");
        printf("|    Password errata.    |\n");
        printf("+------------------------+\n");
        csleep(DEFAULT_SLEEP);
        return 0;
    }
}

/**
 *  Cancellazione di una città con le relative deallocazioni
 */
void remove_city(country_t *country) {
    char city_name[MAX_LONG];
    int city_index = 0,
        i = 0,
        j = 0;

    printf("Inserisci il nome della citta' da eliminare: ");
    fgets(city_name, MAX_LONG, stdin);
    city_name[strcspn(city_name, "\n")] = 0;
    city_name[0] = toupper(city_name[0]);

    if(check_city(country, city_name)) {
        city_index = get_city_index(country, city_name);
        country->city_list = remove_city_from_list(country->city_list, city_index);

        country->ncities -= 1;

        // Deallocazione del vettore relativo alla città da eliminare
        free(country->city_costs_t[city_index]);
        free(country->city_distances_t[city_index]);
        free(country->city_costs_p[city_index]);
        free(country->city_distances_p[city_index]);
        free(country->cities_names[city_index]);

        // Shift nel vettore "principale"
        for(i = city_index; i < country->ncities; i++) {
            country->city_costs_t[i] = country->city_costs_t[i + 1];
            country->city_distances_t[i] = country->city_distances_t[i + 1];
            country->city_costs_p[i] = country->city_costs_p[i + 1];
            country->city_distances_p[i] = country->city_distances_p[i + 1];
            country->cities_names[i] = country->cities_names[i + 1];
        }

        // Reallocazione dei vettori "principali"
        country->city_costs_t = (int **)realloc(country->city_costs_t, country->ncities);
        country->city_distances_t = (int **)realloc(country->city_distances_t, country->ncities);
        country->city_costs_p = (int **)realloc(country->city_costs_p, country->ncities);
        country->city_distances_p = (int **)realloc(country->city_distances_p, country->ncities);
        country->cities_names = (char **)realloc(country->cities_names, country->ncities);

        // Shift e reallocazione dei vettori di riga
        for(j = 0; j < country->ncities; j++) {
            for(i = city_index; i < country->ncities; i++) {
                country->city_costs_t[j][i] = country->city_costs_t[j][i + 1];
                country->city_distances_t[j][i] = country->city_distances_t[j][i + 1];
                country->city_costs_p[j][i] = country->city_costs_p[j][i + 1];
                country->city_distances_p[j][i] = country->city_distances_p[j][i + 1];
            }
            country->city_costs_t[j] = (int *)realloc(country->city_costs_t[j], country->ncities);
            country->city_distances_t[j] = (int *)realloc(country->city_distances_t[j], country->ncities);
            country->city_costs_p[j] = (int *)realloc(country->city_costs_p[j], country->ncities);
            country->city_distances_p[j] = (int *)realloc(country->city_distances_p[j], country->ncities);
        }

        clear_terminal();
        printf("+-----------------------------------+\n");
        printf("|    Città rimossa con successo!    |\n");
        printf("+-----------------------------------+\n");
    } else {
        clear_terminal();
        printf("+---------------------------------------+\n");
        printf("|    La citta' richiesta non esiste.    |\n");
        printf("+---------------------------------------+\n");
        csleep(DEFAULT_SLEEP);
    }
}
