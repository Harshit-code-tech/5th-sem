#include<stdio.h>
#include<stdlib.h>
int gcd(int a, int b){
    if(b == 0)
        return a;
    return gcd(b, a % b);
}
int main(int argc, char *argv[]){
    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = fopen(argv[2], "w");
    if(infile == NULL || outfile == NULL){
        printf("Cannot Open File");
        return 0;
    }
    int n1, n2;
    while(fscanf(infile, "%d %d", &n1, &n2) == 2){
        int res = gcd(n1, n2);
        fprintf(outfile, "The GCD of %d and %d is %d\n", n1, n2, res);
    }
    fclose(infile);
    fclose(outfile);
    outfile = fopen(argv[2], "r");
    char c = getc(outfile);
    while(c != EOF){
        printf("%c", c);
        c = getc(outfile);
    }
    fclose(outfile);
    
    printf("\n22052982: Harshit Ghosh");
    return 0;
}
