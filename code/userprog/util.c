#include<stdio.h>

int isxdigit (int arg) {
    return arg >= '0' && arg <= '9' || arg >= 'a' && arg <= 'f' || arg >= 'A' && arg <= 'F';  
}

int isdigit (int arg) {
    return arg >= '0' && arg <= '9';
}

int islower (int arg) {
    return arg >= 'a' && arg <= 'z'
}

int toupper( int character ){
     return character + 32;
}

size_t strlen( const char * theString ){
    int compt=0;
    while(theString[compt]!='\0'){
        compt++;
    }
    return compt;
}