#ifndef __oop_h__
#define __oop_h__ __oop_h__

#define $(object, function, ...) ((object)->method.function(object, __VA_ARGS__))
#define $new(type) oop_new(NULL, sizeof(type), &type##_method)
#define $delete(object) oop_delete(&object, NULL);

void* oop_new(void** pobject, int type_size, void* type_method, ...);
void oop_delete(void** pobject, ...);
void oop_initial(void* object, void* type_method, ...)
void oop_final(void* object, ...);

#endif/*__oop_h__*/

