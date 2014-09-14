#include "../object/method.h"
/*object*/void* (*release)(void* array, int index);
void (*release_all)(void* array);
/*object*/void* (*insert)(void* array, void* object, int index);
/*object*/void* (*append)(void* array, void* object);
void (*erase)(void* array, int begin, int end);
void (*erase_all)(void* array);
void (*sort)(void* array);
/*object*/void* (*search)(void* array, /*object*/void* key);
