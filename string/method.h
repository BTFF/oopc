#include "../object/method.h" 
void (*attach)(void* string, char* c_string, int length);
char* (*detach)(void* string);
char* (*copy)(void* string, char* c_string, int begin, int end);
char* (*format)(void* string, char* format, ...);
char* (*vformat)(void* string, char* format, va_list ap);
char* (*concatenate)(void* string, char* c_string, int begin, int end);
char* (*erase)(void* string, int begin, int end);
