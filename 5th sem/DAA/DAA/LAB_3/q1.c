#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

// Function prototypes
void mergesort(int a[], int low, int high, int *comparison);
void merge(int a[], int low, int mid, int high, int *comparison);
void process_file(const char *input_filename, const char *output_filename);

#ifdef _WIN32
// Function to get time in nanoseconds on Windows
long long get_time_in_nanoseconds() {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    // The time measurement will be done in the function where it's used
    return start.QuadPart;
}

long long get_elapsed_time(long long start) {
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);
    return (end.QuadPart - start) * 1000000000LL / get_time_in_nanoseconds();
}
#else
// Function to get time in nanoseconds on Linux
long long get_time_in_nanoseconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1e9 + ts.tv_nsec;
}
#endif

int main() {
    int choice;
    while (1) {
        printf("22052982: HARSHIT GHOSH");
        printf("MAIN MENU:\n1. Ascending Data\n2. Descending Data\n3. Random Data\n4. EXIT\nEnter option: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Please enter an integer.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }

        switch (choice) {
            case 1: process_file("inAsce.txt", "outMergeAsce.txt"); break;
            case 2: process_file("inDesc.txt", "outMergeDesc.txt"); break;
            case 3: process_file("inRand.txt", "outMergeRand.txt"); break;
            case 4: printf("Exiting...\n"); exit(0);
            default: printf("Invalid option. Please try again.\n");
        }
    }
    return 0;
}

void merge(int a[], int low, int mid, int high, int *comparison) {
    int n1 = mid - low + 1, n2 = high - mid;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    if (!L || !R) { fprintf(stderr, "Memory allocation failed\n"); exit(EXIT_FAILURE); }

    for (int i = 0; i < n1; i++) L[i] = a[low + i];
    for (int i = 0; i < n2; i++) R[i] = a[mid + i + 1];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
        (*comparison)++;
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
    free(L);
    free(R);
}

void mergesort(int a[], int low, int high, int *comparison) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergesort(a, low, mid, comparison);
        mergesort(a, mid + 1, high, comparison);
        merge(a, low, mid, high, comparison);
    }
}

void process_file(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "r");
    FILE *output = fopen(output_filename, "w");
    if (!input || !output) { perror("Error opening file"); return; }

    int n;
    if (fscanf(input, "%d", &n) != 1) { fprintf(stderr, "Error reading array size.\n"); fclose(input); fclose(output); return; }
    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) { fprintf(stderr, "Memory allocation failed\n"); fclose(input); fclose(output); return; }

    for (int i = 0; i < n; i++) {
        if (fscanf(input, "%d", &arr[i]) != 1) { fprintf(stderr, "Error reading array element.\n"); free(arr); fclose(input); fclose(output); return; }
    }

    fprintf(output, "Before sorting:\n");
    for (int i = 0; i < n; i++) fprintf(output, "%d ", arr[i]);
    fprintf(output, "\n");

    int comparison = 0;
    long long start_time = get_time_in_nanoseconds();

    mergesort(arr, 0, n - 1, &comparison);

    long long end_time = get_time_in_nanoseconds();
    long long time_taken = end_time - start_time;

    fprintf(output, "After sorting:\n");
    for (int i = 0; i < n; i++) fprintf(output, "%d ", arr[i]);
    fprintf(output, "\nNumber of Comparisons: %d\nExecution Time: %lld nanoseconds\n", comparison, time_taken);

    free(arr);
    fclose(input);
    fclose(output);
}
