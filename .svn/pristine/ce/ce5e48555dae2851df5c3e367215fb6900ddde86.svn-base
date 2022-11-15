#include "syscall.h"
void print(char c, int n)
{
    int i;
#if 1
    for (i = 0; i < n; i++) {
        PutChar(c + i);
    }
    PutChar('\n');
#endif
}

//----------------------------------------------------------------------
// putchar.c
//      Print the first 4 letters (abcd)
//----------------------------------------------------------------------

int main()
{
    print('a',4);
    print('1', 6);
    
    // print printable ASCII characters
    print(32, 127 - 32);
    print(128, 255 - 128);
    // Halt();
    return 0;
}