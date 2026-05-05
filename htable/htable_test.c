/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: htable_test.c                                                      *
 * Description: Implements Test module to test Hash Table Data Structure.     *
 * Created: Jun 2018                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include "htable.h"

int htable_test_1000(htable_t htable)
{
  int i, elem, test_status = 0; /* SUCCESS */

  printf("Hash Table Test 1: Verify 1000 inserts and 1000 deletes\n");
  printf("Inserting 1000 entries..\n");
  for (i = 1; i <= 1000; i++) {
    htable_insert(htable, i, i);
  }

  htable_print(htable);

  printf("Deleting 1000 entries..\n");
  for (i = 1000; i >= 1; i--) {
    htable_delete(htable, i);
  }

  htable_print(htable);

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  }

  return test_status;
}

int htable_test_1000_neg(htable_t htable)
{
  int i, elem, test_status = 0; /* SUCCESS */

  printf("Hash Table Test 1: Verify 1000 inserts and 1000 deletes of negative keys\n");
  printf("Inserting 1000 entries..\n");
  for (i = 1; i <= 1000; i++) {
    htable_insert(htable, -i, i);
  }

  htable_print(htable);

  printf("Deleting 1000 entries..\n");
  for (i = 1000; i >= 1; i--) {
    htable_delete(htable, -i);
  }

  htable_print(htable);

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  }

  return test_status;
}

int htable_test_insert_delete_1000(htable_t htable)
{
  int i, elem, test_status = 0; /* SUCCESS */

  printf("Hash Table Test 2: Verify insert followed by delete 1000 times\n");
  for (i = 1; i <= 1000; i++) {
    htable_insert(htable, i, i);
    htable_print(htable);
    htable_delete(htable, i);
  }

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  }

  return test_status;
}

int htable_test_insert_delete_1000_neg(htable_t htable)
{
  int i, elem, test_status = 0; /* SUCCESS */

  printf("Hash Table Test 2: Verify insert followed by delete 1000 times\n");
  for (i = 1; i <= 1000; i++) {
    htable_insert(htable, -i, i);
    htable_print(htable);
    htable_delete(htable, -i);
  }

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  }

  return test_status;
}

int main()
{
  int test_status;
  htable_t htable;

  /* Initialize Hash Table */
  //htable = htable_create(100);
  htable = htable_create(97);

  /* Test 1: Verify 1000 Insert and 1000 Deletes */
  test_status = htable_test_1000(htable);

  /* Test 2: Verify insert and delete 1000 times */
  test_status = htable_test_insert_delete_1000(htable);

  /* Test3: Verify 1000 Insert and 1000 Deletes - negative numbers */
  test_status = htable_test_1000_neg(htable);

  /* Test 4: Verify insert and delete 1000 times - negative numbers */
  test_status = htable_test_insert_delete_1000_neg(htable);

  /* Destroy Hash Table */
  htable_destroy(htable);

  return test_status;
}
