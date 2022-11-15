#include "syscall.h"

void get()
{
    int i = 0;
#if 1
    char s[12];
    GetString(s, 12);
    PutString(s);
    PutChar('\n');
    GetString(s, 40);
    PutString(s);
    PutChar('\n');
#endif
}

//----------------------------------------------------------------------
// getstring.c
//      Get a string (maximum size including '\0': 12) and print it.
//      After, we get a string of size 40 (this value is not valid,
//      so in fact our function will get a maximum of 15 digits)
//----------------------------------------------------------------------

int main()
{
    get();

    return 0;
}