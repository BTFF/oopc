#include "tree.h"

static void* tree_initial(void* tree);
static void* tree_final(void* tree);
static/*(struct object*)*/void* tree_release(void* tree, void* object);
static/*(struct object*)*/void tree_release_all(void* tree);
static/*(struct object*)*/void* tree_insert(void* tree, void* object);
static/*(struct object*)*/void* tree_search(void* tree, void* object);

struct tree_method tree_method =
	{
		.initial = tree_initial,
		.final = NULL
	};

static void* tree_initial(void* tree)
{
	struct tree* self = tree;
	struct tree_method* method = tree->method;

	if(!tree->final)
	{
		method->final = tree_final;
		method->compare = tree_compare;
	}
	return self;
}

static void* tree_final(void* tree)
{
}

static struct tree_node* splay(struct tree_node *root, struct object* key)
{
	struct tree_node	null = {.left = NULL,.right = NULL};
	struct tree_node    *left = &null;
	struct tree_node    *right = &null;
	struct tree_node    *tmp;
	int compare;
START:
	compare = $(key, compare, root->key);
	if(compare < 0)
	{
LEFT:
		if(!(tmp = root->left))
			goto END;
		compare = $(key, compare, tmp->key);
		if(compare < 0)
		{
			root->left = tmp->right;
			tmp->right = root;
			root = tmp;
			if (!(tmp = root->left))
				right->left = root;
			right = root;
			root = tmp;
			goto START;
		} 
		else 
		if(compare > 0)
		{
			right->left = root;
			right = root;
			root = tmp;
			goto RIGHT;
		} 
		else
		{
			right->left = root;
			right = root;
			root = tmp;
		}
		goto END;
	} 
	else 
	if(0 < compare)
	{
RIGHT:
		if(!(tmp = root->right))
			goto END;
		compare = $(key, compare, tmp->key);
		if (compare > 0)
		{
			root->right = tmp->left;
			tmp->left = root;
			root = tmp;
			if (!(tmp = root->right))
				left->right = root;
			left = root;
			root = tmp;
			goto START;
		} 
		else 
		if (compare < 0)
		{
			left->right = root;
			left = root;
			root = tmp;
			goto LEFT;

		} 
		else
		{
			left->right = root;
			left = root;
			root = tmp;
		}
		goto END;
	}
END:
	left->right = root->left;
	right->left = root->right;
	root->left = null.right;
	root->right = null.left;
	return root;
}

static/*(struct object*)*/void* tree_release(void* tree, void* object)
{
}

static/*(struct object*)*/void* tree_insert(void* tree, void* object)
{
}

static/*(struct object*)*/void* tree_search(void* tree, void* object)
{
}

