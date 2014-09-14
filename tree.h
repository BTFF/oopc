#ifndef tree
#define tree tree

#include "object.h"

extern struct tree_method
{
#include "tree/method.h"
} tree_method;

struct tree
{
	struct tree_method* method;
#include "tree/member.h"
};

#endif/*tree*/
