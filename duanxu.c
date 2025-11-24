#include <stdio.h>
int main() {
    unsigned int x = 0x01020304;
    unsigned char *p = (unsigned char *)&x;
    printf("x 的字节序列（从低地址到高地址）: ");
    for (int i = 0; i < 4; i++) {
        printf("%02x ", p[i]);
    }
    printf("\n");
    if (p[0] == 0x04) {
        printf("小端序\n");
    } else if (p[0] == 0x01) {
        printf("大端序\n");
    } else {
        printf("混合端序或其他\n");
    }
    return 0;
}