/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: htable_test.c                                                      *
 * Description: Implements Test module to test Hash Table Data Structure.     *
 * Created: Jun 2018                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <htable.h>

#define HTABLE_TEST_DEBUG         0
#if HTABLE_TEST_DEBUG
#define HTABLE_TEST_PRINT_HTABLE(ht) htable_print(ht)
#else
#define HTABLE_TEST_PRINT_HTABLE(ht)
#endif

int htable_test_1000(htable_t htable)
{
  int i, j, fail_count, result, elem, test_status = 0; /* SUCCESS */

  printf("Hash Table Test 1: Verify 1000 inserts and 1000 deletes\n");
  printf("Inserting 1000 entries..\n");
  for (i = 1; i <= 1000; i++) {
    htable_insert(htable, i, i);
  }
  HTABLE_TEST_PRINT_HTABLE(htable);

  printf("Checking each entry..\n");
  fail_count = 0;
  for (i = 1; i <= 1000; i++) {
    result = htable_find(htable, i, &j);
    if (EOK != result) {
      fail_count++;
      printf("Expected item %d not found\n", i);
    } else if (i != j) {
      fail_count++;
      printf("Expected %d but received %d\n", i, j);
    }
  }

  if (fail_count) {
    printf("%d items failed to return correct value\n", fail_count);
    test_status = 1;
  }

  printf("Deleting all entries..\n");
  for (i = 1000; i >= 1; i--) {
    htable_delete(htable, i);
  }
  HTABLE_TEST_PRINT_HTABLE(htable);

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  } else {
    printf("Test failed!\n");
  }

  printf("\n");

  return test_status;
}

int htable_test_1000_neg(htable_t htable)
{
  int i, j, result, elem, fail_count, test_status = 0; /* SUCCESS */

  printf("Hash Table Test 2: Verify 1000 inserts and 1000 deletes of negative keys\n");
  printf("Inserting 1000 entries..\n");
  for (i = -1; i >= -1000; i--) {
    htable_insert(htable, i, i);
  }
  HTABLE_TEST_PRINT_HTABLE(htable);

  printf("Checking each entry..\n");
  fail_count = 0;
  for (i = -1; i >= -1000; i--) {
    result = htable_find(htable, i, &j);
    if (result != EOK) {
      fail_count++;
      printf("Expected item %d not found\n", i);
    } else if (i != j) {
      fail_count++;
      printf("Expected %d but received %d\n", i, j);
    }
  }

  if (fail_count) {
    printf("%d items failed to return correct value\n", fail_count);
    test_status = 1;
  }

  printf("Deleting all entries..\n");
  for (i = -1; i >= -1000; i--) {
    htable_delete(htable, i);
  }
  HTABLE_TEST_PRINT_HTABLE(htable);

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  } else {
    printf("Test failed!\n");
  }

  printf("\n");

  return test_status;
}

int htable_test_insert_delete_1000(htable_t htable)
{
  int i, j, fail_count, result, elem, test_status = 0; /* SUCCESS */

  printf("Hash Table Test 3: Verify insert followed by delete 1000 times\n");
  fail_count = 0;
  for (i = 1; i <= 1000; i++) {
    htable_insert(htable, i, i);
    HTABLE_TEST_PRINT_HTABLE(htable);
    result = htable_find(htable, i, &j);
    if (EOK != result) {
      fail_count++;
      printf("Expected item %d not found\n", i);
    } else if (i != j) {
      fail_count++;
      printf("Expected %d but received %d\n", i, j);
    }
    htable_delete(htable, i);
  }

  if (fail_count) {
    printf("%d items failed to return correct value\n", fail_count);
    test_status = 1;
  }

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  } else {
    printf("Test failed!\n");
  }

  printf("\n");

  return test_status;
}

int htable_test_insert_delete_1000_neg(htable_t htable)
{
  int i, j, result, fail_count, elem, test_status = 0; /* SUCCESS */

  printf("Hash Table Test 4: Verify insert followed by delete 1000 times\n");
  fail_count = 0;
  for (i = -1; i >= 1000; i--) {
    htable_insert(htable, i, i);
    HTABLE_TEST_PRINT_HTABLE(htable);
    result = htable_find(htable, i, &j);
    if (EOK != result) {
      fail_count++;
      printf("Expected item %d not found\n", i);
    } else if (i != j) {
      fail_count++;
      printf("Expected %d but received %d\n", i, j);
    }
    htable_delete(htable, i);
  }

  if (fail_count) {
    printf("%d items failed to return correct value\n", fail_count);
    test_status = 1;
  }

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  } else {
    printf("Test failed!\n");
  }

  printf("\n");

  return test_status;
}

int main()
{
  int test_status;
  htable_t htable;

  /* Initialize Hash Table */
  htable = htable_create(97);

  printf("\n");
  /* Test 1: Verify 1000 Insert and 1000 Deletes */
  test_status = htable_test_1000(htable);

  /* Test 2: Verify 1000 Insert and 1000 Deletes - negative numbers */
  test_status = htable_test_1000_neg(htable);

  /* Test 3: Verify insert and delete 1000 times */
  test_status = htable_test_insert_delete_1000(htable);

  /* Test 4: Verify insert and delete 1000 times - negative numbers */
  test_status = htable_test_insert_delete_1000_neg(htable);

  /* Destroy Hash Table */
  htable_destroy(htable);

  return test_status;
}
