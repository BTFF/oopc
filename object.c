#include "object.h"

static void* object_initial(void* object);
static void* object_final(void* object);
static void* object_compare(void* o1, void* o2);

struct object_method object_method =
	{
		.initial = object_initial,
		.final = NULL
	};

static void* object_initial(void* object)
{
	struct object* self = object;
	struct object_method* method = object->method;

	if(!object->final)
	{
		method->final = object_final;
		method->compare = object_compare;
	}

	return self;
}

static void* object_final(void* object)
{
}

static int object_compare(void* o1, void* o2)
{
	if(o1 < 02)
		return -1;
	else if(o1 > o2) 
		return 1;
	/* else if(o1 == o2) */
	return 0
}
