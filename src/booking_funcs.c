#include "header.h"

void booking_main(user_t *user) {
    int flag = 0;
    do {
        switch(transport_choice()) {
            case 1:
                // Viaggio aereo
                break;
            case 2:
                // Viaggio treno
                break;
            case 0:
                break;
            default:
                wrong_selection_message();
                break;
        }
    } while(flag);
}

void dijkstra_cost(country_t *country, int **cost_matrix, int start, int end) {
    int *distance = (int *)calloc(country->ncities, sizeof(int)),
        *previous = (int *)calloc(country->ncities, sizeof(int)),
        i = 0,
        j = 0,
        u = 0;
    float cost = 0;
    bool *done = (bool *)calloc(country->ncities, sizeof(bool));

    // Inizializziamo le distanze ad infinito
    // e i nodi precedenti a -1
    for(i = 0; i < country->ncities; i++) {
        distance[i] = __INT_MAX__;
        previous[i] = -1;
    }

    // La distanza del nodo di partenza da sè stesso è 0
    distance[start] = 0;

    // Ricerca del percorso minimo
    for(i = 0; i < country->ncities - 1; i++) {
        // Trova il vertice con distanza minima tra i vertici che non sono stati ancora processati
        // Nella prima iterazione u è sempre uguale a start
        u = get_minimum_distance(country->ncities, distance, done);
        // Segna il vertice trovato come processato
        done[u] = true;
        // Aggiorna i valori delle distanze per i vertici adiacenti a quello trovato
        for(j = 0; j < country->ncities; j++) {
            // Aggiorna la distanza con j solo se questo non è stato processato,
            // se c'è un arco tra u e j e se il peso totale del percorso da start
            // a j passando per u è più piccolo del valore attuale di distance[j]
            if(done[j] == false && cost_matrix[u][j] && distance[u] + cost_matrix[u][j] < distance[j]) {
                previous[j] = u;
                distance[j] = distance[u] + cost_matrix[u][j];
            }
        }
    }

    i = end;
    do {
        cost += cost_matrix[i][previous[i]];
        i = previous[i];
    } while(previous[i] != -1);

    print_shortest_path(country, distance, previous, start, end);
    printf("Costo del viaggio: €%.2f\n", cost);

    free(distance);
    free(previous);
    free(done);
}

void dijkstra_distance(country_t *country, int **distance_matrix, int start, int end) {
    int *distance = (int *)calloc(country->ncities, sizeof(int)),
        *previous = (int *)calloc(country->ncities, sizeof(int)),
        i = 0,
        j = 0,
        u = 0,
        min = 0,
        hr = 0;
    float cost = 0;
    bool *done = (bool *)calloc(country->ncities, sizeof(bool));

    // Inizializziamo le distanze ad infinito
    // e i nodi precedenti a -1
    for(i = 0; i < country->ncities; i++) {
        distance[i] = __INT_MAX__;
        previous[i] = -1;
    }

    // La distanza del nodo di partenza da sè stesso è 0
    distance[start] = 0;

    // Ricerca del percorso minimo
    for(i = 0; i < country->ncities - 1; i++) {
        // Trova il vertice con distanza minima tra i vertici che non sono stati ancora processati
        // Nella prima iterazione u è sempre uguale a start
        u = get_minimum_distance(country->ncities, distance, done);
        // Segna il vertice trovato come processato
        done[u] = true;
        // Aggiorna i valori delle distanze per i vertici adiacenti a quello trovato
        for(j = 0; j < country->ncities; j++) {
            // Aggiorna la distanza con j solo se questo non è stato processato,
            // se c'è un arco tra u e j e se il peso totale del percorso da start
            // a j passando per u è più piccolo del valore attuale di distance[j]
            if(done[j] == false && distance_matrix[u][j] && distance[u] + distance_matrix[u][j] < distance[j]) {
                previous[j] = u;
                distance[j] = distance[u] + distance_matrix[u][j];
            }
        }
    }

    i = end;
    do {
        cost += distance_matrix[i][previous[i]] * 0.1;
        i = previous[i];
    } while(previous[i] != -1);

    if(cost > 60) {
        hr = cost / 60;
        min = cost / 60;
    } else {
        min = cost;
    }

    print_shortest_path(country, distance, previous, start, end);
    printf("Durata del viaggio: ");
    if(hr != 0) {
        if(hr > 1) {
            printf("%d ore e ", hr);
        } else if(hr == 1) {
            printf("%d ora e ", hr);
        }
        if(min > 1) {
            printf("%d minuti.\n", min);
        } else if(min == 1) {
            printf("%d minuto.\n", min);
        }
    } else {
        if(min > 1) {
            printf("%d minuti.\n", min);
        } else if(min == 1) {
            printf("%d minuto.\n", min);
        }
    }

    free(distance);
    free(previous);
    free(done);
}

int get_minimum_distance(int dim, int distance[], bool done[]) {
    int min = __INT_MAX__,
        min_index = 0;

    for(int i = 0; i < dim; i++) {
        if(done[i] == false && distance[i] <= min) {
            min = distance[i];
            min_index = i;
        }
    }
    return min_index;
}

void print_shortest_path(country_t *country, int distance[], int previous[], int start, int end) {
    printf("\n%s -> ", country->cities_names[start]);
    print_path(country->cities_names, previous, end);
    printf("|\n");
}

void print_path(char **cities_names, int previous[], int index) {
    if(previous[index] == -1) {
        return;
    } else {
        print_path(cities_names, previous, previous[index]);
        printf("%s -> ", cities_names[index]);
    }
}

int transport_choice() {
    int choice = 0;

    do {
        clear_terminal();

        printf("Con quale mezzo desideri viaggiare?");
        printf("\n1. Aereo");
        printf("\n2. Treno");
        printf("\n0. Esci");
        printf("\n> ");

        scanf("%d", &choice);
        getchar();

        if(choice < 0 || choice > 2) {
            wrong_selection_message();
        }
    } while(choice < 0 || choice > 2);

    return choice;
}