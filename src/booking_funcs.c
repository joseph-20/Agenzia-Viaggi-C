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

void dijkstra(int **adj_matrix, int dim, int start) {
    int *distance = (int *)calloc(dim, sizeof(int)),
        *previous = (int *)calloc(dim, sizeof(int)),
        i = 0,
        j = 0,
        u = 0;
    bool *done = (bool *)calloc(dim, sizeof(bool));

    // Inizializziamo le distanze ad infinito
    // e i nodi precedenti a -1
    for(i = 0; i < dim; i++) {
        distance[i] = __INT_MAX__;
        previous[i] = -1;
    }

    // La distanza del nodo di partenza da sè stesso è 0
    distance[start] = 0;

    // Ricerca del percorso minimo
    for(i = 0; i < dim - 1; i++) {
        // Trova il vertice con distanza minima tra i vertici che non sono stati ancora processati
        // Nella prima iterazione u è sempre uguale a start
        u = get_minimum_distance(dim, distance, done);
        // Segna il vertice trovato come processato
        done[u] = true;
        // Aggiorna i valori delle distanze per i vertici adiacenti a quello trovato
        for(j = 0; j < dim; j++) {
            // Aggiorna la distanza con j solo se questo non è stato processato,
            // se c'è un arco tra u e j e se il peso totale del percorso da start
            // a j passando per u è più piccolo del valore attuale di distance[j]
            if(done[j] == false && adj_matrix[u][j] && distance[u] + adj_matrix[u][j] < distance[j]) {
                previous[j] = u;
                distance[j] = distance[u] + adj_matrix[u][j];
            }
        }
    }
    print_shortest_path(dim, start, distance, previous);
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

void print_shortest_path(int dim, int start, int distance[], int previous[]) {
    printf("%-10s%-10s%-10s\n", "Vertice", "Distanza", "Percorso");
    for(int i = 0; i < dim; i++) {
        printf("%-5d%-5d%-10d%d -> ", start, i, distance[i], start);
        print_path(previous, i);
        printf("\n");
    }

}

void print_path(int previous[], int index) {
    if(previous[index] == -1) {
        return;
    } else {
        print_path(previous, previous[index]);
        printf("%d ", index);
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