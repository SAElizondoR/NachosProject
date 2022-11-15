#include "syscall.h"

//----------------------------------------------------------------------
// putstring.c
//      Print 2 sample strings.
//      Note: if the string we want to print is longer that buffer size,
//      the last characters are going to be ignored.
//----------------------------------------------------------------------

int main()
{
    PutString("Hello");
    PutChar('\n');
    PutString("This is a test\n");
    PutString("This is a long string to see what happens because 
    the buffer is only 16 bytes");
    PutChar('\n');
    PutString("Ready\n");

    return 12;
}