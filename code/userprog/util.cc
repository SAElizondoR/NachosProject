#include <util.h>

int isdigit (int arg) {
    return arg >= '0' && arg <= '9';
}

int isspace(int arg) {
    return arg == ' ' || arg == '\n' || arg == '\t' || arg == '\v'
        || arg == '\f' || arg == '\r';
}