/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: avl_test.c                                                         *
 * Description: Implements Test module to test AVL Binary Search Tree         *
 *              Data Structure.                                               *
 * Created: Aug 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <avl.h>

void avl_test_print(avl_t t, int bPrint)
{
  printf("Height of the tree: %d\n", avl_height(t));
  if (bPrint) avl_print(t);
  return;
}

int avl_test_sequential(avl_t t, int num, int bPrint)
{
  int i, res, elem;
  int test_status = 0; /* SUCCESS */

  printf("\n");
  printf("Sequential Test: Insert keys sequentially and delete them sequentially\n");
  printf("Inserting %d entries..\n", num);
  for (i = 0; i < num; i++) {
    printf("Inserting %d ..\n", i);
    if ((res = avl_insert(t, i, i))) {
      printf("AVL Insert failed at %d (res=%d)\n", i, res);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
    if (!avl_check(t)) {
      printf("AVL Insert failed at %d. Tree is no longer AVL\n", i);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
  }
  num = i;
  printf("Inserted %d entries..\n", num);
  avl_test_print(t, bPrint);

  printf("Finding %d entries..\n", num);
  for (i = 0; i < num; i++) {
    if ((res = avl_find(t, i, &elem))) {
      printf("AVL Find failed (res=%d)\n", res);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
    if (i != elem) {
      printf("AVL Find: Mismatch (expected=%d, actual=%d)\n", i, elem);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
  }

  printf("Deleting %d entries..\n", num);
  for (i = 0; i < num; i++) {
    printf("Deleting %d ..\n", i);
    avl_delete(t, i);

    if (!avl_check(t)) {
      printf("AVL Delete failed at %d. Tree is no longer AVL\n", i);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
  }
  printf("Deleted %d entries..\n", num);
  avl_test_print(t, 1);

  if (-1 != avl_height(t)) {
    printf("Test failed. Tree is not empty\n");
    test_status = 1;
  }

  if (!test_status) {
    printf("Test completed successfully!\n");
  }

  return test_status;
}

int avl_test_median(avl_t t, int num, int bPrint)
{
  int i, res, elem;
  int test_status = 0; /* SUCCESS */
  //int arr[] = {6, 8, 9, 5, 12, 32, 10, 46, 21, 56, 1, 42, 25, 18};

  printf("\n");
  printf("Median Test: Insert keys from the median out and delete in same sequence\n");
  printf("Inserting %d entries..\n", num);
  for (i = 1; i < num/2; i++) {
    printf("Inserting %d ..\n", num/2 + i);
    if ((res = avl_insert(t, num/2 + i, num/2 + i))) {
      printf("AVL Insert failed at %d (res=%d)\n", num/2 + i, res);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
    if (!avl_check(t)) {
      printf("AVL Insert failed at %d. Tree is no longer AVL\n", num/2 + i);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }

    printf("Inserting %d ..\n", num/2 - i);
    if ((res = avl_insert(t, num/2 - i, num/2 - i))) {
      printf("AVL Insert failed at %d (res=%d)\n", num/2 - i, res);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
    if (!avl_check(t)) {
      printf("AVL Insert failed at %d. Tree is no longer AVL\n", num/2 - i);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
  }
  printf("Inserted %d entries..\n", num);
  avl_test_print(t, bPrint);

  printf("Finding %d entries..\n", num);
  for (i = 1; i < num/2; i++) {
    if ((res = avl_find(t, num/2 + i, &elem))) {
      printf("AVL Find failed (res=%d)\n", res);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
    if (num/2 + i != elem) {
      printf("AVL Find: Mismatch (expected=%d, actual=%d)\n", num/2 + i, elem);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }

    if ((res = avl_find(t, num/2 - i, &elem))) {
      printf("AVL Find failed (res=%d)\n", res);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
    if (num/2 - i != elem) {
      printf("AVL Find: Mismatch (expected=%d, actual=%d)\n", num/2 - i, elem);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
  }

  printf("Deleting %d entries..\n", num);
  for (i = 1; i < num/2; i++) {
    printf("Deleting %d ..\n", num/2 + i);
    avl_delete(t, num/2 + i);
    if (!avl_check(t)) {
      printf("AVL Delete failed at %d. Tree is no longer AVL\n", num/2 + i);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }

    printf("Deleting %d ..\n", num/2 - i);
    avl_delete(t, num/2 - i);
    if (!avl_check(t)) {
      printf("AVL Delete failed at %d. Tree is no longer AVL\n", num/2 - i);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
  }
  printf("Deleted %d entries..\n", num);
  avl_test_print(t, 1);

  if (-1 != avl_height(t)) {
    printf("Test failed. Tree is not empty\n");
    test_status = 1;
  }

  if (!test_status) {
    printf("Test completed successfully!\n");
  }

  return test_status;
}

int avl_test_deleteall(avl_t t, int num, int bPrint)
{
  int i, res, elem;
  int test_status = 0; /* SUCCESS */

  printf("\n");
  printf("DeleteAll Test: Insert entries and delete all using avl_deleteall()..\n");
  printf("Inserting %d entries..\n", num);
  for (i = 0; i < num; i++) {
    printf("Inserting %d ..\n", i);
    if ((res = avl_insert(t, i, i))) {
      printf("AVL Insert failed at %d (res=%d)\n", i, res);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
    if (!avl_check(t)) {
      printf("AVL Insert failed at %d. Tree is no longer AVL\n", i);
      avl_test_print(t, bPrint);
      test_status = 1;
      break;
    }
  }
  num = i;
  printf("Inserted %d entries..\n", num);
  avl_test_print(t, bPrint);

  printf("Deleting all entries..\n");
  avl_deleteall(t);
  printf("Completed deleting all entries\n");
  avl_test_print(t, 1);

  if (-1 != avl_height(t)) {
    printf("Test failed. Tree is not empty\n");
    test_status = 1;
  }

  if (!test_status) {
    printf("AVL Delete All test completed successfully!\n");
  }

  return test_status;
}

int main(void)
{
  int test_result, test_status, test_case;
  avl_t t;

  test_result = test_case = 0;

  /* Create AVL Tree */
  t = avl_create();

  /* Test 1: Verify sequential 64 inserts and 64 deletes */
  test_status = avl_test_sequential(t, 64, 1);
  test_result |= test_status << test_case++;

  /* Test 2: Verify sequential 1000 inserts and 1000 deletes */
  test_status = avl_test_sequential(t, 1024, 0);
  test_result |= test_status << test_case++;

  /* Test 3: Verify median-out 64 inserts and 64 deletes */
  test_status = avl_test_median(t, 64, 1);
  test_result |= test_status << test_case++;

  /* Test 3: Verify median-out 1000 inserts and 1000 deletes */
  test_status = avl_test_median(t, 1024, 0);
  test_result |= test_status << test_case++;

  /* Test 4: Inserts 64 elements and delete all using avl_deleteall() */
  test_status = avl_test_deleteall(t, 64, 1);
  test_result |= test_status << test_case++;

  /* Test 5: Inserts 1000 elements and delete all using avl_deleteall() */
  test_status = avl_test_deleteall(t, 1024, 0);
  test_result |= test_status << test_case++;

  /* Destroy AVL Tree */
  avl_destroy(t);

  if (!test_result) {
    printf("All tests passed!\n");
  } else {
    printf("Test(s) failed. Test Result mask: 0x%x\n", test_result);
  }

  return test_result;
}
