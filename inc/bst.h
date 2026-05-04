/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: bst.h                                                              *
 * Description: Defines interface for Binary Search Tree Datastructure.       *
 * Created: Feb 2019                                                          *
*******************************************************************************
*/
#ifndef BST_H
#define BST_H

#include <err.h>

typedef struct bst_s *bst_t;

bst_t bst_create(void);
void bst_destroy(bst_t t);
int bst_height(bst_t t);
int bst_find(bst_t t, int key, int *pvalue);
int bst_findmin(bst_t t, int *pvalue);
int bst_findmax(bst_t t, int *pvalue);
int bst_insert(bst_t t, int key, int value);
void bst_delete(bst_t t, int key);
void bst_deletemin(bst_t t);
void bst_deletemax(bst_t t);
int bst_delete_all(bst_t t);
void bst_print_inorder(bst_t t);
void bst_print_preorder(bst_t t);
void bst_print_postorder(bst_t t);
void bst_print_levelorder(bst_t t);
void bst_print_tree(bst_t t);

#endif /* BST_H */
