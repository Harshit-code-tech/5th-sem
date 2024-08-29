#include<stdio.h>
#define LENGTH 100
int i;
long int decimal_binary(int dec_num){
    if(dec_num==0)
        return 0;
    else
        return(dec_num % 2 + 10 * decimal_binary(dec_num / 2));
}
int main(int argc, char *argv[]){
    printf("\n22052987: Jyotika Jayani\n");
    char *inputFile = argv[1];
    int arr[LENGTH];
    int n;
    FILE *fp = fopen(inputFile,"r");
    if(fp==NULL){
        printf("Cannot open file");
        return 0;
    }
    printf("Enter array length: ");
    scanf("%d",&n);
    for(i=0; i<n; i++){
        fscanf(fp,"%d",&arr[i]);
    }
    fclose(fp);
    long int bin_arr[LENGTH];
    for(i=0; i<n; i++){
        bin_arr[i] = decimal_binary(arr[i]);
    }
    char *outputFile = argv[2];
    FILE *fp1 = fopen(outputFile,"w");
    if(fp1==NULL){
        printf("Cannot open file to write");
        return 0;
    }
    for(i=0; i<n; i++){
        fprintf(fp1,"The binary equivalent of %d is %ld\n",arr[i],bin_arr[i]);
    }
    fclose(fp1);
    FILE *fp2 = fopen(outputFile,"r");
    char c = fgetc(fp2);
    while(c!=EOF){
        printf("%c",c);
        c=fgetc(fp2);
    }
    fclose(fp2);
    
    return 0;
}
