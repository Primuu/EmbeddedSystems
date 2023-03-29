#include <stdio.h>

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

void showNthBit(size_t const size, void const * const ptr, int n)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            if(j+1 == n%8 && i == (n/8)){
                printf("%dth bit: ", n);
                printf("%u", byte);
            }
        }
    }
    puts("");
}

void changeNthBit(size_t const size, void const * const ptr, int n)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            if(j+1 == n%8 && i == (n/8)){
                b[i] ^= 1 << j;

            }
            else{
                byte = (b[i] >> j) & 1;
            }
        }
    }
}

int main() {
    int i = 5;
    printBits(sizeof(i), &i);
    showNthBit(sizeof(i), &i, 2);
    changeNthBit(sizeof(i), &i, 2);
    changeNthBit(sizeof(i), &i, 3);
    return 0;
}
