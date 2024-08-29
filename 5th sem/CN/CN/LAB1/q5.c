#include <stdio.h>
#include <stdint.h>

int is_little_endian() {
    uint16_t num = 1;
    return *(uint8_t*)&num == 1;
}

void print_bytes(uint32_t num) {
    uint8_t *bytes = (uint8_t*)&num;
    for (int i = 0; i < 4; i++)
        printf("Byte %d: %02X\n", i + 1, bytes[i]);
}

uint32_t convert_endianness(uint32_t num) {
    return ((num >> 24) & 0xFF) | ((num >> 8) & 0xFF00) |
           ((num << 8) & 0xFF0000) | ((num << 24) & 0xFF000000);
}

int main() {
    uint32_t num;
    printf("Enter a 32-bit number (hex, e.g., 0x12345678): ");
    scanf("%x", &num);

    printf("Original number: 0x%08X\n", num);
    printf("System is %s endian.\n", is_little_endian() ? "little" : "big");

    printf("Byte contents:\n");
    print_bytes(num);

    uint32_t converted = convert_endianness(num);
    printf("After conversion: 0x%08X\n", converted);
    printf("Byte contents after conversion:\n");
    print_bytes(converted);

    return 0;
}
