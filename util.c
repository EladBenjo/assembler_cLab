#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *
 */

const char base64Lookup[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int decimalToBinary(int decimal)
{
    int binary = 0;
    int base = 1;

    while (decimal > 0) 
    {
        int remainder = decimal % 2;
        binary += remainder * base;
        decimal /= 2;
        base *= 10;
    }

    return binary;
}

char* binaryToBase64(const char* binary) 
{
    size_t binaryLength = strlen(binary);
    size_t padding = binaryLength % 6 == 0 ? 0 : 6 - (binaryLength % 6);
    size_t base64Length = ((binaryLength + padding) / 6) * 8 + 1;

    char* base64 = (char*)malloc(base64Length * sizeof(char));
    if (base64 == NULL) {
        return NULL;
    }

    size_t i, j;
    for (i = 0, j = 0; i < binaryLength; i += 6, j += 8) {
        unsigned int value = 0;
        for (size_t k = 0; k < 6; k++) {
            value <<= 1;
            if (i + k < binaryLength && binary[i + k] == '1') {
                value |= 1;
            }
        }

        base64[j] = base64Lookup[value >> 2];
        base64[j + 1] = base64Lookup[(value << 4) & 0x3F];
    }

    for (i = 0; i < padding; i++) {
        base64[base64Length - 2 - i] = '=';
    }

    base64[base64Length - 1] = '\0';
    return base64;
}

unsigned long macroHash(int size, char* name) 
{
    unsigned long hash = 0;

    for (int i = 0; name[i] != '\0'; i++) {
        hash = (hash * 31 + name[i]) % size;
    }

    return hash;
}