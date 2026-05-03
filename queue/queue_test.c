/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: queue_test.c                                                       *
 * Description: Implements Test module to test Queue Data Structure.          *
 * Created: July, 2019                                                        *
*******************************************************************************
*/
#include <stdio.h>
#include "queue.h"

void queue_test_display(void *p)
{
  printf("%4d, ", *(int *)p);
}

void queue_test_empty_queue(queue_t q)
{
  int elem;

  while (!queue_dequeue(q, (void *)&elem))
    ;

  return;
}

/* Test Description: Verify 1000 Insert and 1000 Deletes */
int queue_test_1000(queue_t q)
{
  int i, k, elem, res, test_status = 0; /* SUCCESS */

  printf("Queue Test 1: Verify 1000 inserts and 1000 deletes\n");
  printf("Inserting 1000 entries..\n");
  for (i = 1; i <= 1000; i++) {
    if ((res = queue_enqueue(q, (void *)&i))) {
      printf("Queue is full at %d (err=%d)\n", i, res);
      break;
    }
  }

  queue_display(q, queue_test_display);

  /* Dequeu only the entries enqueue, hence starting with i = i - 1.
   * This is in case, queue was full before pushing all 1000 entries
  */
  k = i - 1;
  printf("Deleting %d entries..\n", k);
  for (i = 1; i <= k; i++) {
    if ((res = queue_dequeue(q, (void *)&elem))) {
      printf("Queue Test failed at %d. Queue is Empty! when not expected (err=%d)\n", i, res);
      test_status = 1;
      break;
    }
    if (i != elem) {
      printf("Queue Test failed at %d. Received %d but expected %d\n", i, elem, i);
      test_status = 1;
      break;
    }
  }

  queue_display(q, queue_test_display);
  queue_test_empty_queue(q);

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  }

  return test_status;
}

/* Test Description: Verify insert and delete 1000 times */
int queue_test_insert_delete_1000(queue_t q)
{
  int i, elem, res, test_status = 0; /* SUCCESS */

  printf("Queue Test 2: Verify insert followed by delete 1000 times\n");
  for (i = 1; i <= 1000; i++) {
    if ((res = queue_enqueue(q, (void *)&i))) {
      printf("Queue test failed at %d. Queue is Full, when not expected! (err=%d)\n", i, res);
      test_status = 1;
      break;
    }
    queue_display(q, queue_test_display);
    if ((res = queue_dequeue(q, (void *)&elem))) {
      printf("Queue test failed at %d. Queue is Empty, when not expected! (err=%d)\n", i, res);
      test_status = 1;
      break;
    }
    if (i != elem) {
      printf("Queue test failed at %d. Recieved %d but expected %d\n", i, elem, i);
      test_status = 1;
      break;
    }
  }

  queue_display(q, queue_test_display);
  queue_test_empty_queue(q);

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  }

  return test_status;
}

int main()
{
  int test_status;
  queue_t q;

  /* Initialize Queue */
  q = queue_create(512, sizeof(int));

  /* Test 1: Verify 1000 Insert and 1000 Deletes */
  test_status = queue_test_1000(q);

  /* Test 2: Verify insert and delete 1000 times */
  test_status = queue_test_insert_delete_1000(q);

  /* Destroy Queue */
  queue_destroy(q);

  return test_status;
}
