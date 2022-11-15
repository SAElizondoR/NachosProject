#include "syscall.h"
#include "vsprintf.h"

int main()
{
    //----------------------------------------------------------------------
    // print_test.c
    //      Prints:
    //          "2 hello f"
    //          30 in octal format (36)
    //          2 hexadecimal numbers
    //          an integer and an unsigned integer
    // Note: We cannot print chains of more than MAX_PRINTF_STRING_SIZE (16),
    // because this is the size of our buffer.
    //----------------------------------------------------------------------
    printf("Decimal: %d\n", 2);
    printf("Character: %c\n", 'f');
    printf("Octal: %o\n", 30);
    printf("Hex: %x\t%X\n", 43, 666);
    printf("int: %u\t%i\n", 50, 632);

    return 0;
}