#ifndef array
#define array array

#include "object.h"

extern struct array_method
{
#include "array/method.h"
} array_method;

struct array
{
	struct array_method* method;
#include "array/member.h"
};

#endif/*array*/
