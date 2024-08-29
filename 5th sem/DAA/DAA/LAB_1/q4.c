#include <stdio.h>

void exchange(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

void rotateRight(int *p1, int p2) {
    for (int i = p2 - 1; i > 0; i--) {
        exchange(&p1[i], &p1[i-1]);
    }
}

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int size, rotations;

    // User input for array size
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int A[size];

    // User input for array elements
    printf("Enter %d elements of the array: ", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &A[i]);
    }

    // User input for the number of rotations
    printf("Enter the number of rotations: ");
    scanf("%d", &rotations);

    printf("Before rotate: ");
    printArray(A, size);

    // Perform the rotation
    rotateRight(A, rotations);

    printf("After rotate:  ");
    printArray(A, size);
    printf("22052982: Harshit Ghosh\n");

    return 0;
}
