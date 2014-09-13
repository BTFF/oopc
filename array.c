#include "array.h"

static void* array_initial(void* array);
static void* array_final(void* array);
void* array_release(void* array, int index);
void* array_insert(void* array, void* object, int index);
void* array_erase(void* array, int begin, int end);
void* array_sort(void* array);
void* array_find(void* array, void* object_key);

struct array_method array_method =
	{
		.initial = array_initial,
		.final = NULL
	};

static void* array_initial(void* array)
{
	struct array* self = array;
	struct array_method* method = array->method;

	if(!array->final)
	{
		object_method.initial(self);
		method->initial = array_initial;
		method->final = array_final;
		method->release = array_release;
		method->insert = array_insert;
		method->erase = array_erase;
		method->sort = array_sort;
		method->find = array_find;
	}
	else
		object_method.initial(self);

	self->object = NULL;
	self->size = 0;
	return self;
}

static void* array_final(void* array)
{
	struct array* self = array;
	int i;
	for(i = 0; i < self->size; i++)
	{
		struct object* object = self->object[i];
		$delete(object);
	}
	free(self->object);
}

void* array_release(void* array, int index)
{
	struct array* self = array;
	struct object* object;
	if(index < 0 || array->size < index)
		return NULL;
	object = array->object[index];
	memmove(array->object + index, array->object + index + 1, sizeof(*array->object) * (array->size - (index + 1)));
	return object;
}

void* array_insert(void* array, void* object, int index)
{
}

void* array_erase(void* array, int begin, int end)
{
}

void* array_sort(void* array)
{
}

void* array_find(void* array, void* object_key)
{
}

