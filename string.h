#ifndef string
#define string string

#include "object.h"

extern struct string_method
{
#include "string/method.h"
} string_method;

struct string
{
	struct string_method* method;
#include "string/member.h"
};

#endif/*string*/
