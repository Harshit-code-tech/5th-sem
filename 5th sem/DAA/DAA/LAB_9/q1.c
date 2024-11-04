#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 99999  // Representing infinity as a large value

// Function to read graph from a file
void readGraphFromFile(const char *filename, int graph[MAX][MAX], int *V) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fscanf(file, "%d", V);
    for (int i = 0; i < *V; i++) {
        for (int j = 0; j < *V; j++) {
            fscanf(file, "%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF;  // No path between nodes
            }
        }
    }
    fclose(file);
}

// Floyd-Warshall algorithm
void floydWarshall(int graph[MAX][MAX], int dist[MAX][MAX], int next[MAX][MAX], int V) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF && i != j) {
                next[i][j] = j;
            } else {
                next[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

// Function to reconstruct the path from source to destination
void printPath(int next[MAX][MAX], int u, int v) {
    if (next[u][v] == -1) {
        printf("No path from vertex %d to vertex %d\n", u + 1, v + 1);
        return;
    }
    printf("%d", u + 1);  // Start from the source vertex
    while (u != v) {
        u = next[u][v];
        if (u == -1) {
            printf(" --> (no valid path found)");  // To avoid infinite loop if path is incomplete
            return;
        }
        printf("->%d", u + 1);
    }
    printf("\n");
}

int main() {
    int V;
    int graph[MAX][MAX];
    int dist[MAX][MAX], next[MAX][MAX];

    readGraphFromFile("inDiAdjMat2.txt", graph, &V);

    floydWarshall(graph, dist, next, V);

    printf("Shortest Path Weight Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    int src, dest;
    printf("Enter the source and destination vertex: ");
    scanf("%d %d", &src, &dest);
    src--; dest--;

    if (dist[src][dest] == INF) {
        printf("No path from vertex %d to vertex %d\n", src + 1, dest + 1);
    } else {
        printf("Shortest Path from vertex %d to vertex %d: ", src + 1, dest + 1);
        printPath(next, src, dest);
        printf("Path weight: %d\n", dist[src][dest]);
    }

    return 0;
}

