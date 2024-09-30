#include <stdio.h>

typedef unsigned int INT;
typedef unsigned char CHAR;

typedef struct {
    CHAR ch1, ch2[2], ch3;
} pkt;

void extractBytes(INT num, pkt *p) {
    p->ch1 = num & 0xFF;
    p->ch2[0] = (num >> 8) & 0xFF;
    p->ch2[1] = (num >> 16) & 0xFF;
    p->ch3 = (num >> 24) & 0xFF;
}

void printBytes(const pkt *p) {
    printf("Byte 1: %u\nByte 2: %u\nByte 3: %u\nByte 4: %u\n", p->ch1, p->ch2[0], p->ch2[1], p->ch3);
}

INT ByteToNum(const pkt *p) {
    return (p->ch3 << 24) | (p->ch2[1] << 16) | (p->ch2[0] << 8) | p->ch1;
}

int main() {
    INT num;
    pkt packet;

    printf("Enter Number: ");
    scanf("%u", &num);

    extractBytes(num, &packet);
    printf("After Byte Extraction:\n");
    printBytes(&packet);

    INT aggregatedNum = ByteToNum(&packet);
    printf("After Aggregation:\nNumber: %u\n", aggregatedNum);

    return 0;
}
