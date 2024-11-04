#include <stdio.h>
#include <string.h>

#define MAX 100

// Function to find the length of LCS
int LCS(char *X, char *Y, char *lcs_result) {
    int m = strlen(X);
    int n = strlen(Y);
    int L[MAX][MAX];  // DP table to store lengths of LCS

    // Building the LCS table in bottom-up fashion
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
        }
    }

    // The length of LCS is L[m][n]
    int index = L[m][n];
    int lcs_length = index;

    lcs_result[index] = '\0'; 

    // Backtracking to find the LCS string from L[m][n]
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs_result[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    return lcs_length;
}

int main() {
    char X[MAX], Y[MAX], lcs_result[MAX];

    printf("Enter the first string into an array: ");
    scanf("%s", X);
    printf("Enter the second string into an array: ");
    scanf("%s", Y);

    int lcs_length = LCS(X, Y, lcs_result);

    printf("LCS: %s\n", lcs_result);
    printf("LCS Length: %d\n", lcs_length);
    printf("22052982: Harshit Ghosh\n");

    return 0;
}
