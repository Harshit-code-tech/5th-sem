#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char *name;
    int age;
    int height;
    int weight;
} Person;

Person *persons;
int size = 0;

void swap(Person *a, Person *b) {
    Person temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && persons[left].age < persons[smallest].age)
        smallest = left;

    if (right < n && persons[right].age < persons[smallest].age)
        smallest = right;

    if (smallest != i) {
        swap(&persons[i], &persons[smallest]);
        minHeapify(n, smallest);
    }
}

void buildMinHeap() {
    for (int i = size / 2 - 1; i >= 0; i--)
        minHeapify(size, i);
}

void maxHeapify(int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && persons[left].weight > persons[largest].weight)
        largest = left;

    if (right < n && persons[right].weight > persons[largest].weight)
        largest = right;

    if (largest != i) {
        swap(&persons[i], &persons[largest]);
        maxHeapify(n, largest);
    }
}

void buildMaxHeap() {
    for (int i = size / 2 - 1; i >= 0; i--)
        maxHeapify(size, i);
}

void readData(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fscanf(file, "%d", &size);
    persons = (Person *)malloc(size * sizeof(Person));

    for (int i = 0; i < size; i++) {
        persons[i].name = (char *)malloc(50 * sizeof(char));
        fscanf(file, "%d %s %d %d %d", &persons[i].id, persons[i].name, &persons[i].age, &persons[i].height, &persons[i].weight);
    }

    fclose(file);

    printf("Data read from file:\n");
    for (int i = 0; i < size; i++) {
        printf("ID: %d, Name: %s, Age: %d, Height: %d, Weight: %d\n",
               persons[i].id, persons[i].name, persons[i].age, persons[i].height, persons[i].weight);
    }
}

void writeToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    fprintf(file, "ID Name Age Height Weight\n");
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d %s %d %d %d\n",
                persons[i].id, persons[i].name, persons[i].age, persons[i].height, persons[i].weight);
    }

    fclose(file);
    printf("Heap written to file: %s\n", filename);
}

void displayWeightOfYoungest() {
    buildMinHeap();
    printf("Weight of the youngest person: %d\n", persons[0].weight);
}

void insertPersonToMinHeap() {
    if (size >= MAX) {
        printf("Heap overflow\n");
        return;
    }

    Person newPerson;
    newPerson.name = (char *)malloc(50 * sizeof(char));

    printf("Enter ID, Name, Age, Height, Weight for the new person: ");
    scanf("%d %s %d %d %d", &newPerson.id, newPerson.name, &newPerson.age, &newPerson.height, &newPerson.weight);

    persons = (Person *)realloc(persons, (size + 1) * sizeof(Person));
    persons[size] = newPerson;
    size++;

    buildMinHeap();

    printf("New person inserted into the Min-Heap.\n");
}

void deleteOldestPerson() {
    if (size <= 0) {
        printf("Heap underflow\n");
        return;
    }

    buildMinHeap();

    printf("Deleted oldest person: ID: %d, Name: %s, Age: %d, Height: %d, Weight: %d\n",
           persons[size - 1].id, persons[size - 1].name, persons[size - 1].age, persons[size - 1].height, persons[size - 1].weight);

    size--;
    persons = (Person *)realloc(persons, size * sizeof(Person));
    buildMinHeap();
}

int main() {
    int choice;
    do {
    	printf("\n 22052982: Harshit Ghosh\n");
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readData("data.txt");
                writeToFile("data_output.txt");
                break;
            case 2:
                buildMinHeap();
                writeToFile("min_heap_output.txt");
                break;
            case 3:
                buildMaxHeap();
                writeToFile("max_heap_output.txt");
                break;
            case 4:
                displayWeightOfYoungest();
                break;
            case 5:
                insertPersonToMinHeap();
                writeToFile("min_heap_after_insertion.txt");
                break;
            case 6:
                deleteOldestPerson();
                writeToFile("min_heap_after_deletion.txt");
                break;
            case 7:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);

    for (int i = 0; i < size; i++) {
        free(persons[i].name);
    }
    free(persons);

    return 0;
}

