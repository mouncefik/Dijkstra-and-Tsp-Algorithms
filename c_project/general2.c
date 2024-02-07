#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CITIES 10
#define INFINITY 999

typedef struct City {
    char name[30];
} City;

typedef struct Graph {
    int numCities;
    City* cities;
    int** connecmatrix;
} Graph;

int* tsp(Graph* graph);
double compute_tour_cost(int* tour, Graph* graph);
int next_permutation(int* sequence, int n);
int get_first(int* sequence, int n);
void swap(int* sequence, int i, int j);

Graph* createGraph(int numCities) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numCities = 0;
    graph->connecmatrix = (int**)malloc(numCities * sizeof(int*));
    for (int i = 0; i < numCities; i++) {
        graph->connecmatrix[i] = (int*)malloc(numCities * sizeof(int));
        for (int j = 0; j < numCities; j++) {
            graph->connecmatrix[i][j] = -1;
        }
    }
    graph->cities = (City*)malloc(MAX_CITIES * sizeof(City));

    return graph;
}

void addCity(Graph* graph, const char* cityName) {
    if (graph->numCities < MAX_CITIES) {
        strcpy(graph->cities[graph->numCities].name, cityName);
        graph->numCities++;
    } else {
        printf("Exceeded maximum number of cities.\n");
    }
}

void addConnection(Graph* graph, int city1, int city2, int distance) {
    if (city1 < graph->numCities && city2 < graph->numCities) {
        graph->connecmatrix[city1][city2] = distance;
        graph->connecmatrix[city2][city1] = distance;
    } else {
        printf("Invalid city indices.\n");
    }
}

void displayGraph(Graph* graph) {
    printf("Cities:\n");
    for (int i = 0; i < graph->numCities; i++) {
        printf("%s ", graph->cities[i].name);
    }
    printf("\n\nConnection Matrix:\n");
    for (int i = 0; i < graph->numCities; i++) {
        for (int j = 0; j < graph->numCities; j++) {
            printf("%3d ", graph->connecmatrix[i][j]);
        }
        printf("\n");
    }
}

int* tsp(Graph* graph) {
    int* permutation = (int*)malloc(graph->numCities * sizeof(int));
    for (int i = 0; i < graph->numCities; i++) {
        permutation[i] = i;
    }

    int* bestTour = (int*)malloc(graph->numCities * sizeof(int));
    for (int i = 0; i < graph->numCities; i++) {
        bestTour[i] = permutation[i];
    }

    double bestTourCost = __builtin_inff();

    // Try all (n-1)! tours with returning to the first city
    do {
        double tourCost = compute_tour_cost(permutation, graph);

        if (tourCost < bestTourCost) {
            bestTourCost = tourCost;
            for (int i = 0; i < graph->numCities; i++) {
                bestTour[i] = permutation[i];
            }
        }

    } while (next_permutation(permutation, graph->numCities));

    free(permutation);

    return bestTour;
}


double compute_tour_cost(int* tour, Graph* graph) {
    double cost = 0;

    // Compute the cost of going to each city
    for (int i = 0; i < graph->numCities - 1; i++) {
        int from = tour[i];
        int to = tour[i + 1];
        cost += graph->connecmatrix[from][to];
    }

    // Compute the cost to return to the starting city
    int last = tour[graph->numCities - 1];
    int first = tour[0];
    cost += graph->connecmatrix[last][first];

    return cost;
}

int next_permutation(int* sequence, int n) {
    int first = get_first(sequence, n);
    if (first == -1) {
        return 0;
    }

    int to_swap = n - 1;
    while (sequence[first] >= sequence[to_swap]) {
        --to_swap;
    }

    swap(sequence, first, to_swap);

    // Reverse the sequence from first + 1 to the end
    int start = first + 1;
    int end = n - 1;
    while (start < end) {
        swap(sequence, start++, end--);
    }

    return 1;
}


int get_first(int* sequence, int n) {
    for (int i = n - 2; i > 0; --i) {
        if (sequence[i] < sequence[i + 1]) {
            return i;
        }
    }
    return -1;
}

void swap(int* sequence, int i, int j) {
    int tmp = sequence[i];
    sequence[i] = sequence[j];
    sequence[j] = tmp;
}

int main() {
    Graph* graph = createGraph(5);

    addCity(graph, "Rabat");
    addCity(graph, "Casablanca");
    addCity(graph, "Oujda");
    addCity(graph, "Errachidia");
    addCity(graph, "Agadir");

    addConnection(graph, 0, 1, 87);
    addConnection(graph, 0, 2, 554);
    addConnection(graph, 0, 3, 587);
    addConnection(graph, 1, 2, 614);
    addConnection(graph, 2, 3, 532);
    addConnection(graph, 3, 4, 661);
    addConnection(graph, 2, 4, 1074);
    addConnection(graph, 1, 3, 533);
    addConnection(graph, 0, 4, 647);
    addConnection(graph, 1, 4, 589);

    displayGraph(graph);
    printf("Intermediate Steps:\n");
    int* permutation = (int*)malloc(graph->numCities * sizeof(int));
    for (int i = 0; i < graph->numCities; i++) {
        permutation[i] = i;
    }

    do {
        for (int i = 0; i <= graph->numCities; i++) {
            printf(" -> %s", graph->cities[permutation[i]].name);
        }
        printf("\n");

    } while (next_permutation(permutation, graph->numCities));

    free(permutation);
    int* bestTour = tsp(graph);

    printf("Best Tour: ");
    for (int i = 0; i <= graph->numCities; i++) {
        printf("-> %s  ", graph->cities[bestTour[i]].name);
    }
    printf("\n");

    double tourCost = compute_tour_cost(bestTour, graph);
    printf("Tour cost: %f\n", tourCost);

    return 0;
}
