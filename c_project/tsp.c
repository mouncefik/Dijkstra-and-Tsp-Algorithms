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
