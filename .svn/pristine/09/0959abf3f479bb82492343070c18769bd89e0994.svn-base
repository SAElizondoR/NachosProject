#include "syscall.h"
void scan()
{
#if 1
    /* Imprime les caractères saisis par l'utilisateur dans le terminal
    jusqu'à Ctrl+D soit appuyé (EOF, il est représenté avec la valeur -1) */
    for (;;) {
        char c;
        c = GetChar();
        if (c == -1) {
            PutString("Exit\n");
            break;
        }
        PutChar(c);

    }
#endif
}

int main()
{
    scan();
    // Halt();
}