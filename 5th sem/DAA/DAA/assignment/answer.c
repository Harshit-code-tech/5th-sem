#include <stdio.h>
#include <limits.h>

#define MAX 5  

void optimalBST(int freq[], int n) {
    int cost[MAX][MAX] = {0};      
    int weight[MAX][MAX] = {0};   
    int root[MAX][MAX] = {0};   

    // Initialize weight and cost for single keys
    for (int i = 0; i < n; i++) {
        weight[i][i] = freq[i];
        cost[i][i] = freq[i];
        root[i][i] = i;
    }

    // Build tables for chains of length 2 to n
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            weight[i][j] = weight[i][j - 1] + freq[j];
            cost[i][j] = INT_MAX;

            // Calculate minimum cost by testing each key as root
            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r - 1] : 0) +
                        ((r < j) ? cost[r + 1][j] : 0) + weight[i][j];
                
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }

    // Print Cost and Root matrices
    printf("Cost Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i <= j) printf("%d\t", cost[i][j]);
            else printf("\t");
        }
        printf("\n");
    }

    printf("\nRoot Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i <= j) printf("%d\t", root[i][j]);
            else printf("\t");
        }
        printf("\n");
    }

    printf("\nMinimum Cost of Optimal BST: %d\n", cost[0][n - 1]);
}

int main() {
    int freq[] = {4, 2, 6, 3};  
    int n = sizeof(freq) / sizeof(freq[0]);

    optimalBST(freq, n);
    printf("22052982: HARSHIT GHOSH\n");
    return 0;
}
