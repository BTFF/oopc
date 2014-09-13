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
	if(pp)
	{
		va_list ap;
		va_start(ap, pp);
		do
		{
			struct object* object = *pp;
			$(object, final);
			free(object);
		} while(pp = va_arg(ap, void**));
		va_end(ap);
	}
}

void oop_initial(void* p, void* type_method, ...)
{
	va_list ap;
	struct object* object = p;
	va_start(ap, type_method);
	while(object)
	{
		object->method = type_method;
		$(object, initial);
		if(object = va_arg(ap, void*))
			type_method = va_arg(ap, void*);
	}
	va_end(ap);
}

void oop_final(void* p, ...)
{
	va_list ap;
	struct object* object = p;
	va_start(ap, p)
	while(object)
	{
		$(object, final);
		object = va_arg(ap, void*);
	}
	va_end(ap);
}

