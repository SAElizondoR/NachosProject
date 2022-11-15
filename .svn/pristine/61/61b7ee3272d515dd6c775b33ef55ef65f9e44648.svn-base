#include "syscall.h"

void
print (void *arg)
{
    char c = (char)(long) arg;

    PutChar(c);
    PutChar('\n');

    ThreadExit();

    // do {
    //     c = GetChar();
    // } while (c == '\n');
    // PutChar(c);
    // PutString("HELLOHELLOHELLOHELLOHELLOHELLOHELLOHELLOHELLO");
    // PutChar('\n');
}

//----------------------------------------------------------------------
// MakeThreads
//      Thread test
//----------------------------------------------------------------------
int
main ()
{
    int i;
    char c = 'a';
    PutChar(c);
    PutChar('\n');

    for (i = 1; i < 8; i++) {
        if (ThreadCreate(print, (void *)(long)c + i) == -1)
            PutString("Erreur\n");
    }
        
    
    PutChar(c + i);
    PutChar('\n');

    ThreadExit();

    // do {
    //     c = GetChar();
    // } while (c == '\n');
    
    // PutString("hellohellohellohellohellohellohellohellohellohellohellohello");

    return 0;
}
