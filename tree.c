#include "tree.h"

static struct tree_node* left_most(struct tree_node* root);
static struct tree_node* right_most(struct tree_node* root);
static struct tree_node* splay(struct tree_node *root, struct object* key);

static void* tree_initial(void* tree);
static void* tree_final(void* tree);
static/*object*/void* tree_release(void* tree, void* /*object*/key);
static void tree_release_all(void* tree);
static/*object*/void* tree_insert(void* tree, void* /*object*/key);
static/*object*/void* tree_search(void* tree, void* /*object*/key);

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
		object_method.initial(self);
		method->intial = tree_initial;
		method->final = tree_final;
		method->release = tree_release;
		method->release_all = tree_release_all;
		method->insert = tree_insert;
		method->search = tree_search;
	}
	else
		object_method.initial(self);

	self->root = NULL;
	return self;
}

static void* tree_final(void* tree)
{
	struct tree* self = tree;
	$(self, release_all);
	return self;
}

static/*object*/void* tree_release(void* tree, void* /*object*/key)
{
}

static/*object*/void* tree_insert(void* tree, void* /*object*/key)
{
}

static/*object*/void* tree_search(void* tree, void* /*object*/key)
{
}

static struct tree_node* left(struct tree_node* root)
{
	struct tree_node	null = {.left = NULL,.right = NULL};
	struct tree_node    *left = &null;
	struct tree_node    *right = &null;
	struct tree_node    *tmp;
START:
	if(!(tmp = root->left))
		goto END;
	root->left = tmp->right;
	tmp->right = root;
	root = tmp;
	if (!(tmp = root->left))
		right->left = root;
	right = root;
	root = tmp;
	goto START;
END:
	left->right = root->left;
	right->left = root->right;
	root->left = null.right;
	root->right = null.left;
	return root;
}

static struct tree_node* right(struct tree_node* root)
{
	struct tree_node	null = {.left = NULL,.right = NULL};
	struct tree_node    *left = &null;
	struct tree_node    *right = &null;
	struct tree_node    *tmp;
START:
	if(!(tmp = root->right))
		goto END;
	root->right = tmp->left;
	tmp->left = root;
	root = tmp;
	if (!(tmp = root->right))
		left->right = root;
	left = root;
	root = tmp;
	goto START;
END:
	left->right = root->left;
	right->left = root->right;
	root->left = null.right;
	root->right = null.left;
	return root;
}

static struct tree_node* splay(struct tree_node *root, struct object* key)
{
	struct tree_node	null = {.left = NULL,.right = NULL};
	struct tree_node    *left = &null;
	struct tree_node    *right = &null;
	struct tree_node    *tmp;
	int compare;
START:
	compare = $(key, compare, root->object);
	if(compare < 0)
	{
LEFT:
		if(!(tmp = root->left))
			goto END;
		compare = $(key, compare, tmp->object);
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
		compare = $(key, compare, tmp->object);
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
