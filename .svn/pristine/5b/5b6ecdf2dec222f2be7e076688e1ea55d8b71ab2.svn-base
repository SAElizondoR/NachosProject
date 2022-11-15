
#ifndef VSPRINTF_H
#define VSPRINTF_H

#include <stdarg.h>

int isxdigit (int arg);
int isdigit (int arg);
int islower (int arg);
int toupper( int character );
int strnlen( const char * theString, int maxlen );
unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base);
long simple_strtol(const char *cp,char **endp,unsigned int base);
static int skip_atoi(const char **s);
static char * number(char * str, long num, int base, int size, int precision
	,int type);
int sprintf(char * buf, const char *fmt, ...);
int _vsnprintf(char *buf, int n, const char *fmt, va_list args);
int vsprintf(char *buf, const char *fmt, va_list args);
int sprintf(char * buf, const char *fmt, ...);
int printf (const char *format, ...);

#endif // VSPRINTF_H