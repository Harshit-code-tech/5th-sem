#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100

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
        }
    }
    fclose(file);
}

int minKey(int key[], bool mstSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    return min_index;
}

void printMSTGraph(int mstGraph[MAX][MAX], int V, int totalWeight) {
    printf("Cost Adjacency Matrix of the Minimum Spanning Tree:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", mstGraph[i][j]);
        }
        printf("\n");
    }
    printf("Total Weight of the Spanning Tree: %d\n", totalWeight);
}

void primMST(int graph[MAX][MAX], int V, int start) {
    int parent[MAX];
    int key[MAX];
    bool mstSet[MAX];
    int mstGraph[MAX][MAX] = {0};

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[start] = 0;
    parent[start] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    int totalWeight = 0;
    for (int i = 1; i < V; i++) {
        int u = parent[i];
        int v = i;
        if (u != -1) {
            mstGraph[u][v] = graph[u][v];
            mstGraph[v][u] = graph[u][v];
            totalWeight += graph[u][v];
        }
    }

    printMSTGraph(mstGraph, V, totalWeight);
}

int main() {
    int graph[MAX][MAX], V;
    int startVertex;

    readGraphFromFile("inUnAdjMat.txt", graph, &V);
    
    printf("Enter the starting vertex (1 to %d): ", V);
    scanf("%d", &startVertex);
    startVertex--;  // Convert to 0-based indexing

    if (startVertex < 0 || startVertex >= V) {
        printf("Invalid starting vertex!\n");
        return 1;
    }

    primMST(graph, V, startVertex);
    printf("22052982: Harshit Ghosh\n");
    return 0;
}
