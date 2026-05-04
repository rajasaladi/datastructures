/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: bst_test.c                                                         *
 * Description: Implements Test module to test Binary Search Tree             *
 *              Data Structure.                                               *
 * Created: Feb 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <bst.h>

int main(void)
{
  int i, num, res, elem;
  int test_status = 0; /* SUCCESS */
  bst_t t;
  int arr[] = {6, 8, 9, 5, 12, 32, 10, 46, 21, 56, 1, 42, 25, 18};

  t = bst_create();
  if (!t) {
    printf("Failed creating a BST!\n");
    return 1;
  }

  num = sizeof(arr)/sizeof(arr[0]);
  for (i = 0; i < num; i++) {
    //printf("\nInserting %d ..\n", arr[i]);
    if ((res = bst_insert(t, arr[i], i))) {
      printf("BST Insert failed (res=%d)\n", res);
      test_status = 1;
      break;
    }
    //bst_print_tree(t);
  }
  num = i;
  printf("\nInserted %d entries..\n", num);

  bst_print_tree(t);
  bst_print_inorder(t);
  bst_print_preorder(t);
  bst_print_postorder(t);
  bst_print_levelorder(t);

  printf("\nTesting bst_find()..\n");
  for (i = 0; i < num; i++) {
    if ((res = bst_find(t, arr[i], &elem))) {
      printf("BST Find failed (res=%d)\n", res);
      test_status = 1;
      break;
    }
    if (i != elem) {
      printf("BST Find: Mismatch (expected=%d, actual=%d)\n", i, elem);
      test_status = 1;
      break;
    }
  }
  if (!test_status) {
    printf("BST Find test completed successfully!\n");
  }

  bst_print_tree(t);
#if 0
  printf("\nDeleting %d entries..\n", num);
  for (i = 0; i < num; i++) {
    //printf("\nDeleting %d ..\n", arr[i]);
    bst_delete(t, arr[i]);
    //bst_print_tree(t);
  }
#else
  printf("\nDeleting all entries..\n");
  bst_delete_all(t);
  printf("Completed deleting all nodes\n");
  bst_print_tree(t);
#endif

  bst_destroy(t);

  return 0;
}
