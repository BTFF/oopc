#include "../object/method.h"
/*(struct object*)*/void* (*release)(void* tree, void* object);
/*(struct object*)*/void* (*release_all)(void* tree);
/*(struct object*)*/void* (*insert)(void* tree, void* object);
/*(struct object*)*/void* (*search)(void* tree, void* object);