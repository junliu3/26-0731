//
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    // 4byte
    // 00000000 00000000 00000000 00000000
    int a = 255;
    printf("%032b\n", a);
    // x86 小端对齐，小端字节序
    // 低地址
    //
    // 
    // 高地址

    char *c = (char *)&a;
    printf("%08b\n", *c);
    c++;
    
    printf("%08b\n", *c);
    c++;
    
    printf("%08b\n", *c);
    c++;
    
    printf("%08b\n", *c);
    c++;

    
    return 0;
}