#include "../object/method.h"
/* (struct object*) */void* (*release)(void* array, int index);
void* (*insert)(void* array, void* object, int index);
void* (*erase)(void* array, int begin, int end);
void (*sort)(void* array);
/* (struct object*) */ void* (*search)(void* array, void* object_key);
