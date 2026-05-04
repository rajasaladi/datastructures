/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: avl.c                                                              *
 * Description: Implements AVL Binary Search Tree Data Structure              *
 * Created: Aug 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avl.h>
#include <stack.h>
#include <queue.h>

typedef struct avlnode_s avlnode;

struct avlnode_s {
  avlnode *left;
  avlnode *right;
  int key;
  int data;
  int height;
};

struct avl_s {
  avlnode *root;
  stack1_t st1;
  stack1_t st2;
};

int gDebug = 1;

/******************************************************************************
 *                    P R I V A T E   F U N C T I O N S                       *
 ******************************************************************************
*/

#define TRUE       1
#define FALSE      0

#define MAX(a,b)  (((a) > (b)) ? (a) : (b))

static void avlstack_display_cb(void *param1)
{
  avlnode *p = (avlnode *)param1;

  memcpy(&p, param1, sizeof(avlnode *));
  printf(" (%d, %d),", p->key, p->data);
  return;
}

static int height(avlnode *p)
{
  return (p) ? p->height : -1;
}

static int check_avltree(avlnode *p)
{
  if (!p) return TRUE;
  if (FALSE == check_avltree(p->left)) return FALSE;
  if (FALSE == check_avltree(p->right)) return FALSE;
  if (height(p->left) - height(p->right) > 1 ||
         height(p->left) - height(p->right) < -1) return FALSE;
  return TRUE;
}

/* Single Left Rotation */
static avlnode *avl_left_rotation(avlnode *p)
{
  avlnode *tmp;

  tmp = p->right;
  p->right = tmp->left;
  tmp->left = p;

  p->height = 1 + MAX(height(p->left), height(p->right));
  tmp->height = 1 + MAX(height(tmp->left), height(tmp->right));

  return tmp;
}

/* Single Right Rotation */
static avlnode *avl_right_rotation(avlnode *p)
{
  avlnode *tmp;

  tmp = p->left;
  p->left = tmp->right;
  tmp->right = p;

  p->height = 1 + MAX(height(p->left), height(p->right));
  tmp->height = 1 + MAX(height(tmp->left), height(tmp->right));

  return tmp;
}

/* Left-Right Double Rotation */
static avlnode *avl_left_right_rotation(avlnode *p)
{
  p->left = avl_left_rotation(p->left);
  return avl_right_rotation(p);
}

/* Right-Left Double Rotation */
static avlnode *avl_right_left_rotation(avlnode *p)
{
  p->right = avl_right_rotation(p->right);
  return avl_left_rotation(p);
}

static avlnode *check_balance(avlnode *p)
{
  p->height = 1 + MAX(height(p->left), height(p->right));
  if (height(p->left) - height(p->right) > 1) {
    if (height(p->left->left) - height(p->left->right) > 0) {
      printf("rotate right at %d..\n", p->key);
      p = avl_right_rotation(p);
    } else {
      printf("rotate left-right at %d..\n", p->key);
      p = avl_left_right_rotation(p);
    }
  } else if (height(p->left) - height(p->right) < -1) {
    if (height(p->right->left) - height(p->right->right) < 0) {
      printf("rotate left at %d..\n", p->key);
      p = avl_left_rotation(p);
    } else {
      printf("rotate right-left at %d..\n", p->key);
      p = avl_right_left_rotation(p);
    }
  }

  return p;
}

static void check_balance_path(avlnode **pRoot, avlnode *p, stack1_t st)
{
  avlnode *parent;

  if (!p || !pRoot) return;

  while (!stack_pop(st, &parent)) {
    if (p == parent->left) {
      parent->left = check_balance(p);
    } else {
      parent->right = check_balance(p);
    }
    p = parent;
  }
  *pRoot = check_balance(p);

  return;
}

/*
 * Function
 * Name: avl_find_internal
 * Description: Core function used to traverse tree and find the node for a given key.
 * Params:
 *   p - pointer to root node of the tree.
 *   key - key of the node to be found.
 *   pparent - double pointer to return parent of the node found.
 *   stack - stack to push all the ancestor nodes found in the path.
 * Return:
 *   Returns the pointer to the node found.
 *
*/
static avlnode *avl_find_internal(avlnode *p, int key, stack1_t st)
{
  stack_clear(st);
  while (p) {
    if (key == p->key) break;

    stack_push(st, &p);
    if (key < p->key) {
      p = p->left;
    }
    else {
      p = p->right;
    }
  }

  return p;
}

/*
 * Function
 * Name: avl_unlink_min
 * Description: Unlinks and returns the min node.
 * Params:
 *   pRoot - a double pointer to root. Value of root pointer is used to
 *           traverse the tree. Also gets updated if it is the min node.
 * Return:
 *   Returns the unlinked min node.
 *
*/
static avlnode *avl_unlink_min(avlnode **pRoot, stack1_t st)
{
  avlnode *p, *parent;

  if (!pRoot || !(*pRoot)) return NULL;

  /* find min */
  stack_clear(st);
  p = *pRoot;
  while (p->left) {
    stack_push(st, &p);
    p = p->left;
  }

  /* unlink min */
  parent = NULL;
  stack_pop(st, &parent);
  if (parent) {
    parent->left = p->right;
  } else {
    *pRoot = p->right;
  }
  p->right = NULL;

  check_balance_path(pRoot, parent, st);

  return p;
}

/*
 * Function
 * Name: deleteall
 * Description: Deletes recursively all nodes from the rootnode p.
 * Params:
 *   p - pointer to root node of the tree.
 * Return: None
 *
*/
static void deleteall(avlnode *p)
{
  if (!p) return;

  deleteall(p->left);
  deleteall(p->right);
  free(p);

  return;
}

/******************************************************************************
 *                      P U B L I C   F U N C T I O N S                       *
 ******************************************************************************
*/
/*
 * Function
 * Name: avl_create
 * Description: Allocates and initializes the AVL tree data structure.
 * Params: None
 * Return:
 *   Returns the pointer to allocated AVL tree data structure.
 *
*/
avl_t avl_create(void)
{
  avl_t t;

  t = (avl_t)malloc(sizeof(struct avl_s));
  if (!t) return NULL;

  t->root = NULL;
  t->st1 = stack_create(512, sizeof(avlnode *));
  if (!t->st1) {free(t); return NULL;}

  t->st2 = stack_create(512, sizeof(avlnode *));
  if (!t->st2) {stack_destroy(t->st1); free(t); return NULL;}

  return t;
}

/*
 * Function
 * Name: avl_destroy
 * Description: De-Allocates the AVL tree data structure.
 * Params:
 *   t - AVL tree
 * Return: None
 *
*/
void avl_destroy(avl_t t)
{
  if (!t) return;

  deleteall(t->root);
  stack_destroy(t->st1);
  stack_destroy(t->st2);
  free(t);

  return;
}

/*
 * Function
 * Name: avl_find
 * Description: Finds an entry in AVL tree and returns its value.
 * Params:
 *   t - AVL tree
 *   key - key
 *   pvalue - pointer to object where value is copied
 * Return:
 *   RES_EOK or error code.
 *
*/
int avl_find(avl_t t, int key, int *pvalue)
{
  avlnode *p;

  if (!t || !pvalue) return RES_EBADPARM;

  p = avl_find_internal(t->root, key, NULL);
  if (!p) return RES_ENOTEXIST;

  *pvalue = p->data;
  return RES_EOK;
}

/*
 * Function
 * Name: avl_insert
 * Description: Inserts a key and value into the AVL tree.
 * Params:
 *   t - AVL tree
 *   key - key
 *   value - value
 * Return: RES_EOK or error code.
 *
*/
int avl_insert(avl_t t, int key, int value)
{
  int count = 0;
  avlnode *p, *parent;

  if (!t) return RES_EBADPARM;

  p = avl_find_internal(t->root, key, t->st1);
  if (p) return RES_EEXISTS;

  p = (avlnode *)malloc(sizeof(avlnode));
  if (!p) return RES_ENOMEMORY;

  p->key = key;
  p->data = value;
  p->left = p->right = NULL;
  p->height = 0;

  parent = NULL;
  stack_pop(t->st1, &parent);
  if (parent) {
    if (key < parent->key) {
      parent->left = p;
    } else {
      parent->right = p;
    }
  } else {
    t->root = p;
  }

  check_balance_path(&t->root, parent, t->st1);

  return RES_EOK;
}

/*
 * Function
 * Name: avl_delete
 * Description: Deletes a node from the AVL tree.
 * Params:
 *   t - AVL tree
 *   key - key
 * Return:
 *   None
 *
*/
void avl_delete(avl_t t, int key)
{
  avlnode *p, *parent, *new;

  if (!t) return;

  p = avl_find_internal(t->root, key, t->st1);
  if (!p) return;

  if (!p->left) {
    new = p->right;
  } else if (!p->right) {
    new = p->left;
  } else {
    new = avl_unlink_min(&p->right, t->st2);
    new->left = p->left;
    new->right = p->right;
    new = check_balance(new);
  }

  parent = NULL;
  stack_pop(t->st1, &parent);
  if (parent) {
    if (p == parent->left) {
      parent->left = new;
    } else {
      parent->right = new;
    }
  } else {
    t->root = new;
  }

  free(p);

  check_balance_path(&t->root, parent, t->st1);

  return;
}

/*
 * Function
 * Name: avl_deleteall
 * Description: Deletes all nodes from the AVL tree.
 * Params:
 *   t - AVL tree
 * Return:
 *   None
 *
*/
void avl_deleteall(avl_t t)
{
  if (!t) return;

  deleteall(t->root);
  t->root = NULL;

  return;
}

/*
 * Function
 * Name: avl_check
 * Description: Checks if the input AVL tree is actually an AVL tree.
 * Params:
 *   t - AVL tree
 * Return: height of the tree.
 *    0: if it does not satisfy the rules of an AVL tree.
 *    non-zero: if it is an AVL tree.
 *
*/
int avl_check(avl_t t)
{
  return (t) ? check_avltree(t->root) : 0;
}

/*
 * Function
 * Name: avl_height
 * Description: Returns height of the tree.
 * Params:
 *   t - AVL tree
 * Return: height of the tree.
 *   -1: if no nodes (i.e. zero nodes).
 *    0: if only root node.
 *
*/
int avl_height(avl_t t)
{
  return (t) ? height(t->root) : -1;
}

/*
 * Function
 * Name: avl_print_old  <== OBSOLETE/REMOVE ==>
 * Description: Prints AVL tree in some tree form.
 * Params:
 *   t - AVL tree
 * Return:
 *   None
 *
*/
void avl_print_old(avl_t t)
{
  queue_t q;
  avlnode *p;
  int i, count, non_null, height;
  char buf[512];

  if (!t || !t->root) {
    printf("AVL tree is Empty!\n");
    return;
  }

  q = queue_create(512, sizeof(avlnode *));
  if (!q) {
    printf("Not enough memory!\n");
    return;
  }

  height = avl_height(t);
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
 * Name: avl_print
 * Description: Prints AVL tree in proper tree form.
 * Params:
 *   t - AVL tree
 * Return:
 *   None
 *
*/
void avl_print(avl_t t)
{
  queue_t q;
  avlnode *p;
  int i, j, count, null, height;
  int n, nl, bl, e, b, w;

  /*
   * (Concept borrowed from heap implementation)
   * n - no. of elements at last level.
   * e - no of spaces within which an element is printed.
   * b - no of spaces before and after each element at last level.
   * w - total no. of characters for the last level.
   *     w = n*e + 2*n*b.
   * nl - no. of elements at a given level.
   * bl - no. of spaces before and after each element at a given level.
   *            w - nl*e
   *      bl = ----------
   *              2*nl
   * Note: A new line is printed and new bl is calculated at each level
   *
   * Example: (This routine prints like below)
   *
   *                    3               
   *            1               7       
   *        0       2       5       9   
   *      *   *   *   *   4   6   8  10 
   *
  */

  if (!t || !t->root) {
    printf("AVL tree is Empty!\n");
    return;
  }

  q = queue_create(512, sizeof(avlnode *));
  if (!q) {
    printf("Not enough memory!\n");
    return;
  }

  null = 0;
  height = avl_height(t);
  printf("Height: %d\n", height);

  n = 1 << height; /* nodes at last level = 2^height */
  e = 2, b = 1;
  w = n*e + 2*n*b;
  queue_enqueue(q, (void *)&t->root);
  while((count = queue_length(q))) {
    if (null == count) break;
    null = 0;
    nl = count;
    bl = (w - nl*e)/(2*nl);
    for (i = 0; i < count; i++) {
      queue_dequeue(q, (void *)&p);
      /* Print bl spaces before */
      for (j = 0; j < bl; j++) {
        printf(" ");
      }
      if (p) {
        /* Print the element within e characters  */
        printf("%2d", p->key); /* Note: Make sure n in %nd is equal to e */
        if (!p->left) null++;
        if (!p->right) null++;
        queue_enqueue(q, (void *)&p->left);
        queue_enqueue(q, (void *)&p->right);
      } else {
        printf(" *");
        null += 2;
        queue_enqueue(q, (void *)&p);
        queue_enqueue(q, (void *)&p);
      }
      /* Print bl spaces after */
      for (j = 0; j < bl; j++) {
        printf(" ");
      }
    }
    printf("\n");
  }
  queue_destroy(q);

  return;
}
