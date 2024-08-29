#include <stdio.h>

typedef unsigned char CHAR;
typedef unsigned int INT;

void extractBytes(INT x, CHAR *bytes) {
    bytes[0] = x & 0xFF;
    bytes[1] = (x >> 8) & 0xFF;
    bytes[2] = (x >> 16) & 0xFF;
    bytes[3] = (x >> 24) & 0xFF;
}

void printBytes(const CHAR *bytes) {
    printf("Byte 1 (least significant): %u\n", bytes[0]);
    printf("Byte 2: %u\n", bytes[1]);
    printf("Byte 3: %u\n", bytes[2]);
    printf("Byte 4 (most significant): %u\n", bytes[3]);
}

int main() {
    INT num;
    CHAR bytes[4];
    
    printf("Enter a number: ");
    scanf("%u", &num);
    
    extractBytes(num, bytes);
    printBytes(bytes);
    
    return 0;
}
