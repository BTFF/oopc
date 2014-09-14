#ifndef tree
#define tree tree

#include "object.h"

/* splay tree */

struct tree_node
{
	struct tree_node* left;
	struct tree_node* right;
	struct object* object;
};

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
