//Find second largest and second smallest element in an array
#include<stdio.h>
#include<limits.h>
int i;
void secondLargest( int arr[] , int n){
    int first,second;
    first = second = INT_MIN;
    if(n<2){
        printf("Invalid input");
        return;
    }

    for(i=0; i<n; i++){
        if(arr[i] > first){
            second = first;
            first = arr[i];
        }
        else if(arr[i] > second && arr[i]!=first)
            second = arr[i];
    }
    if(second==INT_MIN)
        printf("There is no second largest element");
    else
        printf("Second Largest Element: %d\n",second);
}

void secondSmallest( int arr[] , int n){
    int first,second;
    first = second = INT_MAX;
    if(n<2){
        printf("Invalid input");
        return;
    }

    for(i=0; i<n; i++){
        if(arr[i] < first){
            second = first;
            first = arr[i];
        }
        else if(arr[i] < second && arr[i]!=first)
            second = arr[i];
    }
    if(second==INT_MAX)
        printf("There is no second largest element");
    else
        printf("Second Smallest Element: %d",second);
}

int main(){
    int n;
    printf("Enter size of array: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter %d elements in array: ",n);
    for(i=0; i<n; i++){
        scanf("%d",&arr[i]);

    }
    secondLargest(arr,n);
    secondSmallest(arr,n);
    printf("22052982: Harshit Ghosh");
}