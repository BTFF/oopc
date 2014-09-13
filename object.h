#ifndef object
#define object object

#include "oopc.h"

extern struct object_method
{
#include "object/method.h"
} object_method;

struct object
{
	struct object_method* method;
#include "object/member.h"
};

#endif/*object*/
