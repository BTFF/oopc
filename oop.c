#include "oop.h"
#include "object.h"

void* oop_new(void** pp, int type_size, void* type_method, ...)
{
	struct object* object;
	va_list ap;
	if(object = malloc(type_size))
	{
		object->method = type_method;
		if(!$(object, initial))
		{	
			$(object, final);
			free(object);
			object = NULL;
		}
	}
	if(!pp)
		return object;
	*pp = object;

	va_start(ap, type_method);
	while(pp = va_arg(ap, void**))
	{
		type_size = va_arg(ap, int);
		type_method = va_arg(ap, void*);

		if(object = malloc(type_size))
		{
			object->method = type_method;
			if(!$(object, initial))
			{	
				$(object, final);
				free(object);
				object = NULL;
			}
		}
		*pp = object;
	}
	va_end(ap);

	return NULL;
}

void oop_delete(void** pp, ...)
{
	struct object* object;
}

