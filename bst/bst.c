/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: bst.c                                                              *
 * Description: Implements Binary Search Tree Data Structure                  *
 * Created: Feb 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bst.h>
#include <queue.h>
#include <stack.h>

typedef struct bstnode_s bstnode;

struct bstnode_s {
  bstnode *left;
  bstnode *right;
  int key;
  int data;
};

struct bst_s {
  bstnode *root;
};

/******************************************************************************
 *                    P R I V A T E   F U N C T I O N S                       *
 ******************************************************************************
*/

/*
 * Function
 * Name: bst_unlink_min
 * Description: Unlinks and returns the min node.
 * Params:
 *   proot - a double pointer to root. Value of root pointer is used to
 *           traverse the tree. Also gets updated if it is the min node.
 * Return:
 *   Returns the unlinked min node.
 *
*/
static bstnode *bst_unlink_min(bstnode **proot)
{
  bstnode *p, *parent;

  if (!proot || !(*proot)) {
    return NULL;
  }

  parent = NULL;
  p = *proot;
  while (p->left) {
    parent = p;
    p = p->left;
  }

  if (parent) {
    parent->left = p->right;
  } else {
    *proot = p->right;
  }
  p->right = NULL;

  return p;
}

/*
 * Function
 * Name: bst_find_internal
 * Description: Core function used to traverse tree and find the node for a given key.
 * Params:
 *   p - pointer to root node of the tree.
 *   key - key of the node to be found.
 *   pparent - double pointer to return parent of the node found.
 * Return:
 *   Returns the pointer to the node found.
 *
*/
static bstnode *bst_find_internal(bstnode *p, int key, bstnode **pparent)
{
  bstnode *parent;

  parent = NULL;
  while (p) {
    if (key < p->key) {
      parent = p; p = p->left;
    }
    else if (key > p->key) {
      parent = p; p = p->right;
    }
    else {
      break;
    }
  }

  if (pparent) {
    *pparent = parent;
  }

  return p;
}

/******************************************************************************
 *                      P U B L I C   F U N C T I O N S                       *
 ******************************************************************************
*/
/*
 * Function
 * Name: bst_create
 * Description: Allocates and initializes the BST data structure.
 * Params: None
 * Return:
 *   Returns the pointer to allocated BST data structure.
 *
*/
bst_t bst_create(void)
{
  bst_t t;

  t = (bst_t)malloc(sizeof(struct bst_s));
  if (t) {
    t->root = NULL;
  }

  return t;
}

/*
 * Function
 * Name: bst_destroy
 * Description: De-Allocates the BST data structure.
 * Params:
 *   t - BST
 * Return: None
 *
*/
void bst_destroy(bst_t t)
{
  queue_t q;
  bstnode *p;

  if (!t)
    return;

  if (!t->root) {
    free(t);
    return;
  }

  /* Free nodes */
  q = queue_create(512, sizeof(bstnode *));
  if (q) {
    p = t->root;
    while (p) {
      if (p->left) {
        queue_enqueue(q, &p->left);
      }
      if (p->right) {
        queue_enqueue(q, &p->right);
      }
      free(p);
      queue_dequeue(q, &p);
    }
  }
  queue_destroy(q);

  /* Free main datastructure */
  free(t);

  return;
}

/*
 * Function
 * Name: bst_find
 * Description: Finds an entry in BST and returns its value.
 * Params:
 *   t - BST
 *   key - key
 *   pvalue - pointer to object where value is copied
 * Return:
 *   RES_EOK or error code.
 *
*/
int bst_find(bst_t t, int key, int *pvalue)
{
  bstnode *p;

  if (!t || !pvalue)
    return RES_EBADPARM;

  p = bst_find_internal(t->root, key, NULL);
  if (!p) {
    return RES_ENOTEXIST;
  }

  *pvalue = p->data;
  return RES_EOK;
}

/*
 * Function
 * Name: bst_findmin
 * Description: Finds the entry with lowest key in BST and returns its value.
 * Params:
 *   t - BST
 *   pvalue - pointer to object where value is copied
 * Return:
 *   RES_EOK or error code.
 *
*/
int bst_findmin(bst_t t, int *pvalue)
{
  bstnode *p;

  if (!t || !pvalue) return RES_EBADPARM;
  if (!t->root) return RES_ENOTEXIST;

  p = t->root;
  while (p->left) {
    p = p->left;
  }

  *pvalue = p->data;
  return RES_EOK;
}

/*
 * Function
 * Name: bst_findmax
 * Description: Finds the entry with highest key in BST and returns its value.
 * Params:
 *   t - BST
 *   pvalue - pointer to object where value is copied
 * Return:
 *   RES_EOK or error code.
 *
*/
int bst_findmax(bst_t t, int *pvalue)
{
  bstnode *p;

  if (!t || !pvalue) return RES_EBADPARM;
  if (!t->root) return RES_ENOTEXIST;

  p = t->root;
  while (p->right) {
    p = p->right;
  }

  *pvalue = p->data;
  return RES_EOK;
}

/*
 * Function
 * Name: bst_insert
 * Description: Inserts a key and value into the BST.
 * Params:
 *   t - BST
 *   key - key
 *   value - value
 * Return: RES_EOK or error code.
 *
*/
int bst_insert(bst_t t, int key, int value)
{
  bstnode *p, *parent, *new;

  if (!t) return RES_EBADPARM;

  p = bst_find_internal(t->root, key, &parent);
  if (p) return RES_EEXISTS;

  new = (bstnode *)malloc(sizeof(bstnode));
  if (!new) return RES_ENOMEMORY;

  new->key = key;
  new->data = value;
  new->left = new->right = NULL;
  if (parent) {
    if (key < parent->key) {
      parent->left = new;
    } else {
      parent->right = new;
    }
  } else {
    t->root = new;
  }

  return RES_EOK;
}

/*
 * Function
 * Name: bst_delete
 * Description: Deletes a node from the BST.
 * Params:
 *   t - BST
 *   key - key
 * Return:
 *   None
 *
*/
void bst_delete(bst_t t, int key)
{
  bstnode *p, *parent, *new;

  if (!t) return;

  p = bst_find_internal(t->root, key, &parent);
  if (!p) return;

  if (!p->left) { /* one or no child */
    new = p->right;
  }
  else if (!p->right) { /* one child */
    new = p->left;
  }
  else { /* two children */
    new = bst_unlink_min(&p->right);
    new->left = p->left;
    new->right = p->right;
  }

  if (parent) {
    if (key < parent->key) {
      parent->left = new;
    } else {
      parent->right = new;
    }
  } else {
    t->root = new;
  }

  free(p);

  return;
}

/*
 * Function
 * Name: bst_delete_all
 * Description: Deletes all nodes from the BST.
 * Params:
 *   t - BST
 * Return: RES_EOK or error code.
 *
*/
int bst_delete_all(bst_t t)
{
  bstnode *p, *tmp;
  stack1_t st;

  if (!t || !t->root) return RES_EOK;

  st = stack_create(128, sizeof(bstnode *));
  if (!st) return RES_ENOMEMORY;

  p = t->root;
  while (p) {
    if (p->left && p->right) {      /* two children */
      stack_push(st, (void *)&p->right);
      tmp = p; p = p->left;
      free(tmp);
    } else if (p->left) {        /* left child only */
      tmp = p; p = p->left;
      free(tmp);
    } else if (p->right) {      /* right child only */
      tmp = p; p = p->right;
      free(tmp);
    } else {                         /* no children */
      free(p); p = NULL;
      stack_pop(st, (void *)&p);
    }
  }
  stack_destroy(st);
  t->root = NULL;

  return RES_EOK;
}

/*
 * Function
 * Name: bst_height_rec
 * Description: Returns height of the tree using recursive approach.
 * Params:
 *   t - BST
 * Return: height of the tree.
 *   -1: if no nodes (i.e. zero nodes).
 *    0: if only root node.
 *
*/
static int bst_height_rec(bstnode *p)
{
  int left, right;

  if (!p) return -1;

  left = bst_height_rec(p->left);
  right = bst_height_rec(p->right);
  return 1 + ((left > right) ? left : right);
}

/*
 * Function
 * Name: bst_height
 * Description: Returns height of the tree.
 * Params:
 *   t - BST
 * Return: height of the tree.
 *   -1: if no nodes (i.e. zero nodes).
 *    0: if only root node.
 *
*/
int bst_height(bst_t t)
{
  if (!t) return -1;
  return bst_height_rec(t->root);
}

/*
 * Function
 * Name: bst_print_tree
 * Description: Prints BST in some tree form.
 * Params:
 *   t - BST
 * Return:
 *   None
 *
*/
void bst_print_tree(bst_t t)
{
  queue_t q;
  bstnode *p;
  int i, count, non_null, height;
  char buf[512];

  if (!t || !t->root) {
    printf("BST is Empty!\n");
    return;
  }

  q = queue_create(512, sizeof(bstnode *));
  if (!q) {
    printf("Not enough memory!\n");
    return;
  }

  height = bst_height(t);
  printf("Height: %d\n", height);
  queue_enqueue(q, (void *)&t->root);
  while((count = queue_length(q))) {
    buf[0] = '\0';
    non_null = 0;
    for (i = 0; i < count; i++) {
      queue_dequeue(q, (void *)&p);
      if (p) {
        non_null++;
        sprintf(buf + strlen(buf), " %2d", p->key);
        //printf(" %2d", p->key);
        queue_enqueue(q, (void *)&p->left);
        queue_enqueue(q, (void *)&p->right);
      } else {
        sprintf(buf + strlen(buf), "  *");
        //printf("  *");
        //queue_enqueue(q, (void *)&p);
        //queue_enqueue(q, (void *)&p);
      }
    }

    if (!non_null) {
      break;
    }

    printf("%s\n", buf);
  }
  printf("\n");

  queue_destroy(q);

  return;
}

/*
 * Function
 * Name: bst_print_inorder_iter
 * Description: Prints tree in-order.
 * Params:
 *   p - pointer to root node of the tree.
 * Return:
 *   None
 *
*/
static void bst_print_inorder_iter(bstnode *p)
{
  stack1_t s;

  if (!p) return;

  if (!(s = stack_create(512, sizeof(bstnode *)))) {
    return;
  }

  while (1) {
    if (p) {
      stack_push(s, (void *)&p);
      p = p->left;
    } else {
      if (stack_pop(s, (void *)&p)) {
        break;
      }
      printf(" %d", p->key);
      p = p->right;
    }
  }

  stack_destroy(s);

  return;
}

/*
 * Function
 * Name: bst_print_inorder_rec
 * Description: Prints tree in-order using recursive approach.
 * Params:
 *   p - pointer to root node of the tree.
 * Return:
 *   None
 *
*/
static void bst_print_inorder_rec(bstnode *p)
{
  if (p) {
    bst_print_inorder_rec(p->left);
    printf(" %d", p->key);
    bst_print_inorder_rec(p->right);
  }

  return;
}

/*
 * Function
 * Name: bst_print_preorder_iter
 * Description: Prints tree pre-order.
 * Params:
 *   p - pointer to root node of the tree.
 * Return:
 *   None
 *
*/
static void bst_print_preorder_iter(bstnode *p)
{
  stack1_t s;

  if (!p) return;

  if (!(s = stack_create(512, sizeof(bstnode *)))) {
    return;
  }

  while (1) {
    if (p) {
      printf(" %d", p->key);
      stack_push(s, (void *)&p);
      p = p->left;
    } else {
      if (stack_pop(s, (void *)&p)) {
        break;
      }
      p = p->right;
    }
  }

  stack_destroy(s);

  return;
}

/*
 * Function
 * Name: bst_print_preorder_rec
 * Description: Prints tree pre-order using recursive approach.
 * Params:
 *   p - pointer to root node of the tree.
 * Return:
 *   None
 *
*/
static void bst_print_preorder_rec(bstnode *p)
{
  if (p) {
    printf(" %d", p->key);
    bst_print_preorder_rec(p->left);
    bst_print_preorder_rec(p->right);
  }

  return;
}

/*
 * Function
 * Name: bst_print_postorder_iter
 * Description: Prints tree post-order.
 * Params:
 *   p - pointer to root node of the tree.
 * Return:
 *   None
 *
*/
static void bst_print_postorder_iter(bstnode *p)
{
  stack1_t s;
  bstnode *q;

  if (!p) return;

  if (!(s = stack_create(1024, sizeof(bstnode *)))) {
    return;
  }

  while (1) {
    if (p) {
      if (p->right) {
        stack_push(s, (void *)&p->right);
      }
      stack_push(s, (void *)&p);
      p = p->left;
    }
    else {
      if (stack_pop(s, (void *)&p)) {
        break;
      }
      q = NULL;
      stack_top(s, (void *)&q);
      if (p->right && q == p->right) {
        stack_pop(s, (void *)&q);
        stack_push(s, (void *)&p);
        p = q;
      } else {
        printf(" %d", p->key);
        p = NULL;
      }
    }
  }

  stack_destroy(s);

  return;
}

/*
 * Function
 * Name: bst_print_postorder_rec
 * Description: Prints tree post-order using recursive approach.
 * Params:
 *   p - pointer to root node of the tree.
 * Return:
 *   None
 *
*/
static void bst_print_postorder_rec(bstnode *p)
{
  if (p) {
    bst_print_postorder_rec(p->left);
    bst_print_postorder_rec(p->right);
    printf(" %d", p->key);
  }

  return;
}

/*
 * Function
 * Name: bst_print_levelorder_internal
 * Description: Prints tree in level order.
 * Params:
 *   p - pointer to root node of the tree.
 * Return:
 *   None
 *
*/
static void bst_print_levelorder_internal(bstnode *p)
{
  queue_t q;
  int i, count;

  if (!p) return;

  q = queue_create(512, sizeof(bstnode *));
  if (!q) {
    printf("Not enough memory!\n");
    return;
  }

  queue_enqueue(q, (void *)&p);
  while ((count = queue_length(q))) {
    for (i = 0; i < count; i++) {
      queue_dequeue(q, (void *)&p);
      printf(" %d", p->key);
      if (p->left) {
        queue_enqueue(q, (void *)&p->left);
      }
      if (p->right) {
        queue_enqueue(q, (void *)&p->right);
      }
    }
  }
  queue_destroy(q);

  return;
}

/*
 * Function
 * Name: bst_print_inorder
 * Description: Prints BST in In-Order
 * Params:
 *   t - BST
 * Return:
 *   None
 *
*/
void bst_print_inorder(bst_t t)
{
  if (!t || !t->root) {
    printf("BST is Empty!\n");
    return;
  }

  printf("In-Order\n");
  bst_print_inorder_iter(t->root);
  printf("\n");
  printf("(Recursive)\n");
  bst_print_inorder_rec(t->root);
  printf("\n");

  return;
}

/*
 * Function
 * Name: bst_print_preorder
 * Description: Prints BST in Pre-Order
 * Params:
 *   t - BST
 * Return:
 *   None
 *
*/
void bst_print_preorder(bst_t t)
{
  if (!t || !t->root) {
    printf("BST is Empty!\n");
    return;
  }

  printf("Pre-Order\n");
  bst_print_preorder_iter(t->root);
  printf("\n");
  printf("(Recursive)\n");
  bst_print_preorder_rec(t->root);
  printf("\n");

  return;
}

/*
 * Function
 * Name: bst_print_postorder
 * Description: Prints BST in Post-Order
 * Params:
 *   t - BST
 * Return:
 *   None
 *
*/
void bst_print_postorder(bst_t t)
{
  if (!t || !t->root) {
    printf("BST is Empty!\n");
    return;
  }

  printf("Post-Order\n");
  bst_print_postorder_iter(t->root);
  printf("\n");
  printf("(Recursive)\n");
  bst_print_postorder_rec(t->root);
  printf("\n");

  return;
}

/*
 * Function
 * Name: bst_print_levelorder
 * Description: Prints BST in Level-Order
 * Params:
 *   t - BST
 * Return:
 *   None
 *
*/
void bst_print_levelorder(bst_t t)
{
  if (!t || !t->root) {
    printf("BST is Empty!\n");
    return;
  }

  printf("Level-Order\n");
  bst_print_levelorder_internal(t->root);

  return;
}
