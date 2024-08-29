#include <stdio.h>
#include <stdlib.h>

void callByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    printf("After swapping (Value): a = %d, b = %d\n", a, b);
}

void callByReference(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char *argv[]) {
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    printf("Before swapping: a = %d, b = %d\n", x, y);
    callByValue(x, y);
    callByReference(&x, &y);
    printf("After swapping (Reference): a = %d, b = %d\n", x, y);

    return 0;
}
