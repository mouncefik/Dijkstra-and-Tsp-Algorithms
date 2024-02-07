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

Graph* createGraph(int numCities);
void addCity(Graph* graph, const char* cityName);
void addConnection(Graph* graph, int city1, int city2, int distance);
void displayGraph(Graph* graph);
void dijkstra(Graph* graph, int startNode);


