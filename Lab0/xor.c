#include <stdio.h>

int Xor(int x, int y){
    return ((~x) & y) | (x & (~y));
}

int main() {
    int a = 7, b = 3;
    printBits(sizeof(a),&a);
    printBits(sizeof(b),&b);
    printf("Output = %d\n", a ^ b);
    printf("%d\n",Xor(a,b));
    return 0;
}