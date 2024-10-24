#include <stdio.h>
#include <limits.h>

#define MAX 100

// Function to print the optimal parenthesization
void printOptimalParens(int s[MAX][MAX], int i, int j) {
    if (i == j) {
        printf("A%d", i + 1);
    } else {
        printf("(");
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        printf(")");
    }
}

// Function to implement matrix chain multiplication
void matrixChainOrder(int p[], int n) {
    int m[MAX][MAX];  // M-table to store the minimum scalar multiplications
    int s[MAX][MAX];  // S-table to store the splits
    int i, j, k, L, q;

    // Initialize the M-table to 0 for diagonal elements (base case)
    for (i = 1; i < n; i++)
        m[i][i] = 0;

    // Fill the M-table using dynamic programming
    for (L = 2; L < n; L++) {  // L is the chain length
        for (i = 1; i <= n - L; i++) {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k < j; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    // Print M-table
    printf("M Table:\n");
    for (i = 1; i < n; i++) {
        for (j = i; j < n; j++) {
            printf("%7d ", m[i][j]);
        }
        printf("\n");
    }

    // Print S-table
    printf("\nS Table:\n");
    for (i = 1; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            printf("%7d ", s[i][j]);
        }
        printf("\n");
    }

    // Print the optimal parenthesization
    printf("\nOptimal parenthesization: ");
    printOptimalParens(s, 1, n - 1);
    printf("\nThe optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n - 1]);
}

int main() {
    int n, i;
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[MAX];  // To store dimensions of matrices
    printf("Enter row and column size of A1: ");
    scanf("%d%d", &p[0], &p[1]);

    for (i = 2; i <= n; i++) {
        printf("Enter row and column size of A%d: ", i);
        int row, col;
        scanf("%d%d", &row, &col);
        if (row != p[i - 1]) {
            printf("Incompatible dimensions!\n");
            return 1;
        }
        p[i] = col;
    }

    matrixChainOrder(p, n + 1);
    return 0;
}
