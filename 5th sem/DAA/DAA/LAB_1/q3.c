//Find number of elements that have duplicates and element with max repetition
#include<stdio.h>
#include<stdlib.h>
int i;
#define MAX_SIZE 1000
int countDuplicates(int arr[], int n, int count[]){
    int duplicates = 0;
    for(i=0; i<n; i++){
        count[arr[i]]++;
        if(count[arr[i]] == 2)
            duplicates++;
    }
    return duplicates;
}

int elementFrequency(int count[] , int size){
    int maxCount = 0 , maxElement = 0;
    for(i=0; i<size; i++){
        if(count[i] > maxCount){
        maxCount = count[i];
        maxElement = i;
        }
    }
    return maxElement;
}

int main(){
    int n;
    int count[MAX_SIZE] = {0};
    printf("Enter size of array: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter %d elements in array: ",n);
    for(i=0; i<n; i++){
        scanf("%d",&arr[i]);

    }
    printf("Number of elements with duplicate values: %d\n",countDuplicates(arr,n,count));
    printf("Most Frequent Element: %d",elementFrequency(count,MAX_SIZE));
    printf("\n22052982: Harshit Ghosh");

}