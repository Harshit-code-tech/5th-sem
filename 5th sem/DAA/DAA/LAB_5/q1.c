#include <stdio.h>
#include <stdlib.h>

struct ITEM {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
};

void swap(struct ITEM* a, struct ITEM* b) {
    struct ITEM temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct ITEM items[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && items[left].profit_weight_ratio > items[largest].profit_weight_ratio)
        largest = left;

    if (right < n && items[right].profit_weight_ratio > items[largest].profit_weight_ratio)
        largest = right;

    if (largest != i) {
        swap(&items[i], &items[largest]);
        heapify(items, n, largest);
    }
}

void heapSort(struct ITEM items[], int n) {

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(items, n, i);

    for (int i = n - 1; i >= 0; i--) {

        swap(&items[0], &items[i]);

        heapify(items, i, 0);
    }
}
float fractionalKnapsack(struct ITEM items[], int n, float knapsack_capacity) {
    float total_profit = 0.0;

    for (int i = 0; i < n; i++) {
        if (knapsack_capacity >= items[i].item_weight) {
            knapsack_capacity -= items[i].item_weight;
            total_profit += items[i].item_profit;
            printf("Item No: %d\tProfit: %.6f\tWeight: %.6f\tAmount to be taken: %.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, 1.0);
        } else {
            float fraction = knapsack_capacity / items[i].item_weight;
            total_profit += items[i].item_profit * fraction;
            printf("Item No: %d\tProfit: %.6f\tWeight: %.6f\tAmount to be taken: %.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            break;
        }
    }

    return total_profit;
}

int main() {
    int n;
    float knapsack_capacity;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct ITEM items[n];

    for (int i = 0; i < n; i++) {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%f", &knapsack_capacity);

    heapSort(items, n);

    float max_profit = fractionalKnapsack(items, n, knapsack_capacity);

    printf("Maximum profit: %.6f\n", max_profit);

    return 0;
}
