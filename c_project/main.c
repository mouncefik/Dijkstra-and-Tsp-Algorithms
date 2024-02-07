
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