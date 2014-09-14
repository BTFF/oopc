#include "array.h"

static void* array_initial(void* array);
static void* array_final(void* array);
static void* array_release(void* array, int index);
static void array_release_all(void* array);
static void* array_insert(void* array, void* object, int index);
static void* array_append(void* array, void* object);
static void* array_erase(void* array, int begin, int end);
static void array_erase_all(void* array);
static void array_sort(void* array);
static void* array_search(void* array, void* object_key);

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
		method->release_all = array_release_all;
		method->insert = array_insert;
		method->append = array_append;
		method->erase = array_erase;
		method->erase_all = array_erase_all;
		method->sort = array_sort;
		method->search = array_search;
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
	return NULL;
}

static void* array_release(void* array, int index)
{
	struct array* self = array;
	struct object* object;
	if(index < 0 || self->size < index)
		return NULL;
	object = self->object[index];
	memmove(self->object + index, self->object + index + 1, sizeof(*self->object) * (self->size - (index + 1)));
	self->size--;
	return object;
}

static void array_release_all(void* array)
{
	struct array* self = array;
	if(self->object)
		free(self->object);
	self->size = 0;
	self->object = NULL;
}

static void* array_insert(void* array, void* insert, int index)
{
	struct array* self = array;
	struct object** object;
	if(index < 0 || self->size < index)
		return NULL;
	if(!(object = realloc(self->object, sizeof(*self->object) * (self->size + 1))))
		return NULL;
	self->object = object;
	if(0 < self->size)
		memmove(self->object + index + 1, self->object + index, sizeof(*self->object) * (self->size - index));
	self->size++;
	self->object[index] = insert;
	return insert;
}

static void* array_append(void* array, void* append)
{
	struct array* self = array;
	void** object;

	if(!(object = realloc(self->object, sizeof(*self->object) * (self->size + 1))))
		return NULL;
	self->object = object;
	self->object[self->size] = append;
	self->size++;
	return append;
}

static void* array_erase(void* array, int begin, int end)
{
	struct array* self = array;
	struct object* object;
	int i;
	if(begin >= end || begin < 0 || self->size < end)
		return NULL;
	object = self->object[index];
	for(i = begin; i < end; i++)
		$delete(self->object[i]);
	memmove(self->object + begin, self->object + end, sizeof(*self->object) * (self->size - end));
	self->size -= end - begin;
	return self;
}

static void array_erase_all(void* array)
{
	struct array* self = array;
	int i;
	for(i = 0; i < self->size; i++)
		$delete(self->object[i]);
	$(self, release_all);
}

static int compare(void* key, void* member)
{
	struct object** pobject_key = key;
	struct object** pmember = member;
	return $(*pobject_key, compare, *pmember);
}

static void array_sort(void* array)
{
	struct array* self = array;
	qsort(self->object, self->size, sizeof(*self->object), compare);
}

static /*object*/void* array_search(void* array, /*object*/void* key)
{
	struct array* self = array;
	struct object** match = bsearch(&key, self->object, self->size, sizeof(*self->object), compare)
	if(match)
		return *match;
	return NULL;
}

