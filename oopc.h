#ifndef __oopc_h__
#define __oopc_h__ __oopc_h__

#define $(object, function, ...) ((object)->method.function(object, __VA_ARGS__))
#define $new(type) oop_new(NULL, sizeof(type), &type##_method)
#define $delete(object) oop_delete(&object, NULL);

void* oop_new(void** object, int type_size, void* type_method, ...);
void oop_delete(void** object, ...);
void oop_initial(void* objecd, int type_size, void* type_method, ...)
void oop_delete(void* object, ...);

#endif/*__oopc_h__*/
