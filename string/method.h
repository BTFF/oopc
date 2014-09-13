#include "../object/method.h" 
void (*attach)(void* string, char* c_string);
char* (*release)(void* string);
char* (*copy)(void* string, char* c_string, int begin, int end);
char* (*format)(void* string, char* format, ...);
char* (*vformat)(void* string, char* format, va_list ap);
void* (*trim)(void* string, int begin, int end); 
