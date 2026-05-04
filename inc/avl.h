/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: avl.h                                                              *
 * Description: Defines interface for AVL Binary Search Tree Datastructure.   *
 * Created: Aug 2019                                                          *
*******************************************************************************
*/
#ifndef AVL_H
#define AVL_H

#include <err.h>

typedef struct avl_s *avl_t;

avl_t avl_create(void);
void avl_destroy(avl_t t);
int avl_height(avl_t t);
int avl_find(avl_t t, int key, int *pvalue);
int avl_insert(avl_t t, int key, int value);
void avl_delete(avl_t t, int key);
void avl_deleteall(avl_t t);
int avl_check(avl_t t);
void avl_print(avl_t t);

#endif /* AVL_H */
