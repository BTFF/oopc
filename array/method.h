#include "../object/method.h"
void* (*release)(void* array, int index);
void* (*insert)(void* array, void* object, int index);
void* (*erase)(void* array, int begin, int end);
void* (*sort)(void* array);
void* (*find)(void* array, void* object_key);
