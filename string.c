#include <stdarg.h>
#include "string.h"

static void* string_initial(void* string);
static void* string_final(void* string);
static int string_compare(void* s1, void* s2);
static void string_attach(void* string, char* c_string, int length);
static char* string_detach(void* string);
static char* string_copy(void* string, char* c_string, int begin, int end);
static char* string_format(void* string, char* format, ...);
static char* string_vformat(void* string, char* format, va_list ap);
static char* string_concatenate(void* string, char* c_string, int begin, int end);
static char* string_erase(void* string, int begin, int end);

struct string_method string_method =
	{
		.initial = string_initial,
		.final = NULL
	};

static void* string_initial(void* string)
{
	struct string* self = string;
	struct string_method* method = self->method;

	if(!self->final)
	{
		object_method.initial(self);
		method->initial = string_initial;
		method->final = string_final;
		method->compare = string_compare;
		method->attach = string_attach;
		method->detach = string_detach;
		method->format = string_format;
		method->vformat = string_vformat;
		method->concatenate = string_concatenate;
		method->erase = string_erase;
	}
	else
		object_method.initial(self);

	string->length = 0;
	string->c_string = NULL;
	return self;
}

static void* string_final(void* string)
{
	struct string* self = string;
	struct string_method* method = self->method;

	if(self->c_string)
		free(self->c_string);
	object_method.final(string);
	return self;
}

static int string_compare(void* s1, void* s2)
{
	struct string* string1 = s1;
	struct string* string2 = s2;
	struct string_method* method = string1->method;

	if(string1->c_string && string2->c_string)
		return strcmp(string1->c_string, string2->c_string);
	else
	if(string1->c_string && !string2->c_string)
		return 1;
	else
	if(!string1->c_string && string2->c_string)
		return -1;
	/* else if(!string1->c_string && !string2->c_string) */
	return 0;
}

static void string_attach(void* string, char* c_string, int length)
{
	struct string* self = string;
	struct string_method* method = self->method;
	if(self->c_string)
		free(self->c_string);
	self->length = length;
	self->c_string = c_string;
}

static char* string_detach(void* string)
{
	struct string* self = string;
	struct string_method* method = self->method;
	char* c_string = self->c_string;

	self->length = 0;
	self->c_string = NULL;
	return c_string;
}

static char* string_copy(void* string, char* from, int begin, int end)
{
	struct string* self = string;
	int length = end - begin;
	char* c_string = malloc(length + 1);

	if(!c_string)
		return NULL;
	memcpy(c_string, from + begin, length);
	c_string[length] = '\0';
	if(self->c_string)
		free(self->c_string);
	self->length = length;
	self->c_string = c_string;
	return c_string;
}

static char* string_format(void* string, char* format, ...)
{
	struct string* self = string;
	struct string_method* method = self->method;
	char* c_string;
	va_list ap;

	va_start(ap, format);
	c_string = method->vformat(self, format, ap);
	va_end(ap);
	return c_string;
}

static char* string_vformat(void* string, char* format, va_list ap)
{
	struct string* self = string;
	int length;
	char* c_string = NULL;
	if(-1 == (length = vasprintf(&c_string, format, ap)))
	{
		if(c_string)
			free(c_string);
		c_string = NULL;
	}
	else
	{
		if(self->c_string)
			free(self->c_string);
		self->length = length;
		self->c_string = c_string;
	}
	return c_string;
}

static char* string_concatenate(void* string, char* from, int begin, int end)
{
	struct string* self = string;
	int length;
	char* c_string;

	if(being > end)
		return NULL;
	length = self->length + end - begin;
	if(!(c_string = realloc(self->c_string, length + 1)))
		return NULL;
	memcpy(c_string + self->length, from + begin, end - begin);
	c_string[length] = '\0';
	self->length = length;
	self->c_string = c_string;
	return c_string;
}

static char* string_erase(void* string, int begin, int end)
{
	struct string* self = string;
	if(begin < 0 || self->length < end)
		return NULL;
	memmove(self->c_string + begin, self->c_string + end, self->length - end);
	self->length -= end - begin;
	self->c_string[self->length] = '\0';
	if(0 < self->legnth)
		self->c_string = realloc(self->c_string, self->length + 1);
	else
		free(self->c_string);
	return self->c_string;
}

