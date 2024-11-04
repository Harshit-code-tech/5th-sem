#include <stdio.h>
#include <limits.h>

#define INF INT_MAX
#define MAX 100

// Function to print the path from source to destination using the previous node array
void printPath(int prev[], int i) {
    if (prev[i] == -1)
        return;
    printPath(prev, prev[i]);
    printf("->%d", i + 1);
}

// Function to find the vertex with the minimum distance value that hasn't been visited
int minDistance(int dist[], int visited[], int n) {
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function implementing Dijkstra's algorithm
void dijkstra(int graph[MAX][MAX], int src, int n) {
    int dist[MAX], visited[MAX], prev[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        prev[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);
        if (u == -1) 
            break;
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    // Display the results
    printf("Source\tDestination\tCost\tPath\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t", src + 1, i + 1);
        if (dist[i] == INF) {
            printf("-\t-\n");
        } else {
            printf("%d\t%d", dist[i], src + 1);
            printPath(prev, i);
            printf("\n");
        }
    }
}

int main() {
    FILE *file = fopen("inDiAdjMat1.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int n, graph[MAX][MAX];

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);
    printf("Enter the Source Vertex (1 to %d): ", n);
    int src;
    scanf("%d", &src);
    src--;

    if (src < 0 || src >= n) {
        printf("Invalid source vertex!\n");
        return 1;
    }

    // Reading the graph from file
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF;  // No edge between different nodes
            }
        }
    }
    fclose(file);

    dijkstra(graph, src, n);
    printf("22052982: Harshit Ghosh\n");

    return 0;
}
