#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <limits.h>
#define MAX_CITIES 10  // Flexible maximum number of cities
#define INFINITY 999

typedef struct City {
    char name[30];
} City;

typedef struct Graph {
    int numCities;
    City* cities;
    int** connecmatrix;
} Graph;


Graph* createGraph(int numCities) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numCities = 0; // Initialize with city Number 0

    // Allocate memory for the connection matrix
    graph->connecmatrix = (int**)malloc(numCities * sizeof(int*));
    for (int i = 0; i < numCities; i++) {
        graph->connecmatrix[i] = (int*)malloc(numCities * sizeof(int));
        for (int j = 0; j < numCities; j++) {
            graph->connecmatrix[i][j] = -1; // Initialize to -1 where is no connection
        }
    }
    // Allocate memory for the array of cities
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



void dijkstra(Graph* graph, int startNode) {
    int n = graph->numCities;
    int cost[MAX_CITIES][MAX_CITIES], distance[MAX_CITIES], pred[MAX_CITIES];
    int visited[MAX_CITIES], count, mindistance, nextnode, i, j;

    // Creating cost matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (graph->connecmatrix[i][j] == -1)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = graph->connecmatrix[i][j];

    for (i = 0; i < n; i++) {
        distance[i] = cost[startNode][i];
        pred[i] = startNode;
        visited[i] = 0;
    }

    distance[startNode] = 0;
    visited[startNode] = 1;
    count = 1;

    while (count < n - 1) {
        mindistance = INFINITY;
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }

        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i]) {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }
    
    for (int i = 0; i < n; i++) {
        // Printing the shortest distance
        if (i != startNode) {
        printf("\nThe shortest Distance from %s to %s: %d", graph->cities[startNode].name, graph->cities[i].name, distance[i]);
        }

        // Printing the path
        printf("\nPath: %s", graph->cities[startNode].name);

        // Store the cities in an array
        int path[MAX_CITIES];
        int pathLength = 1;

        j = i;
        do {
            path[pathLength++] = j;
            j = pred[j];
        } while (j != startNode);

        // Print the cities in reverse order
        for (int k = pathLength -1; k >= 0; k--) {
            printf(" -> %s", graph->cities[path[k]].name);
             }

        printf("\n");
        }
  
       
}



int main() {
    Graph* graph = createGraph(5);

    addCity(graph, "Rabat");
    addCity(graph, "Casablanca");
    addCity(graph, "Oujda");
    addCity(graph, "Errachidia");
    addCity(graph, "Agadir");

    addConnection(graph, 0, 1, 87);
    addConnection(graph, 1, 2, 614);
    addConnection(graph, 2, 3, 532);
    addConnection(graph, 3, 4, 661);
    addConnection(graph, 2, 4, 1074);
    addConnection(graph, 1, 3, 533);
    addConnection(graph, 0, 4, 547);
    addConnection(graph, 1, 4, 465);

    displayGraph(graph);
    
    printf("\n\nDijkstra's Shortest Paths:\n");
    dijkstra(graph, 2);
    
}