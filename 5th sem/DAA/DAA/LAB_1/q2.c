//PrefixSum array
#include<stdio.h>
int i;

void prefixSum(int arr[], int n){
    int sum = 0;
    int prefixSum[n];
    for(i=0; i<n; i++){

        sum += arr[i];
        prefixSum[i] = sum;


    }
    printf("Prefix Sum Array: ");
    for(i=0; i<n; i++)
        printf("%d ",prefixSum[i]);
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
    prefixSum(arr,n);
    printf("22052982: Harshit Ghosh");
}