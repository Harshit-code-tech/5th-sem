#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

void swap(int *x, int *y);
int partition(int arr[], int low, int high, int *comparison);
void quicksort(int arr[], int low, int high, int *comparison);
void driver(FILE *input, int arr[], FILE *output);
void print_array(FILE *output, int arr[], int n);

#ifdef _WIN32
double get_time_in_seconds() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    return (double)start.QuadPart / frequency.QuadPart;
}
#else
double get_time_in_seconds() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}
#endif

int main() {
    FILE *inputfile, *outputfile;
    int choice = 0;
    int arr[500];

    do {
        
        printf("22052982: HARSHIT GHOSH");
        printf("MAIN MENU:\n");
        printf("1. Ascending Data\n2. Descending Data\n3. Random Data\n4. EXIT\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputfile = fopen("inAsce.txt", "r");
                outputfile = fopen("outQuickAsce.txt", "w");
                if (inputfile && outputfile) {
                    driver(inputfile, arr, outputfile);
                    fclose(inputfile);
                    fclose(outputfile);
                } else {
                    printf("Error opening file.\n");
                }
                break;
            case 2:
                inputfile = fopen("inDesc.txt", "r");
                outputfile = fopen("outQuickDesc.txt", "w");
                if (inputfile && outputfile) {
                    driver(inputfile, arr, outputfile);
                    fclose(inputfile);
                    fclose(outputfile);
                } else {
                    printf("Error opening file.\n");
                }
                break;
            case 3:
                inputfile = fopen("inRand.txt", "r");
                outputfile = fopen("outQuickRand.txt", "w");
                if (inputfile && outputfile) {
                    driver(inputfile, arr, outputfile);
                    fclose(inputfile);
                    fclose(outputfile);
                } else {
                    printf("Error opening file.\n");
                }
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int arr[], int low, int high, int *comparison){
    int i = low, j = high;
    int pivot = arr[low]; // starting element as pivot element
    while (i < j) {
        while (arr[i] <= pivot && i <= high - 1) {
            i++;
            (*comparison)++;
        }
        while (arr[j] > pivot && j >= low + 1) {
            j--;
            (*comparison)++;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
            (*comparison)++;
        }
    }
    swap(&arr[low], &arr[j]);
    (*comparison)++;
    return j;
}

void quicksort(int arr[], int low, int high, int *comparison){
    if (low < high) {
        int partitionIndex = partition(arr, low, high, comparison);
        quicksort(arr, low, partitionIndex - 1, comparison);
        quicksort(arr, partitionIndex + 1, high, comparison);
    }
}

void print_array(FILE *output, int arr[], int n) {
    for (int i = 0; i < n; i++) {
        fprintf(output, "%d ", arr[i]);
    }
    fprintf(output, "\n");
}

void driver(FILE *input, int arr[], FILE *output) {
    int n;
    int comparison = 0; // Initialize comparison counter locally

    // Read size of array
    fscanf(input, "%d", &n);

    // Read array
    for (int i = 0; i < n; i++) {
        fscanf(input, "%d", &arr[i]);
    }

    // Printing array before sorting
    fprintf(output, "Before sorting:\n");
    print_array(output, arr, n);

    // Sorting and calculating execution time
    double start = get_time_in_seconds();

    quicksort(arr, 0, n - 1, &comparison);

    double end = get_time_in_seconds();
    long time_taken = (long)((end - start) * 1e9);

    // Printing array after sorting
    fprintf(output, "After sorting:\n");
    print_array(output, arr, n);

    fprintf(output, "Number of Comparisons: %d\n", comparison);
    fprintf(output, "Execution Time: %ld nanoseconds\n", time_taken);
}
