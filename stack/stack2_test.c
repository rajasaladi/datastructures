/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: stack2_test.c                                                      *
 * Description: Implements Test module to test Data Structure with two stacks *
 *              in one array.                                                 *
 * Created: January, 2019                                                     *
*******************************************************************************
*/
#include <stdio.h>
#include <stack2.h>

void display_integer(void *p)
{
  int *q;
  if (!p) return;

  q = (int *)p;
  printf(" %d", *q);
  return;
}

int stack2_test_1000(stack2_t st)
{
  int i, k, elem, res, test_status = 0; /* SUCCESS */

  printf("Stack Test 1: Verify 1000 pushs and 1000 pops\n");
  printf("Pushing 1000 entries..\n");
  for (i = 1; i <= 1000; i++) {
    if ((res = stack2_push1(st, (void *)&i))) {
      printf("Stack is full at %d (err=%d)\n", i, res);
      break;
    }
    if ((res = stack2_push2(st, (void *)&i))) {
      printf("Stack is full at %d (err=%d)\n", i, res);
      break;
    }
  }

  stack2_display(st, display_integer);

  /* Pop only the entries pushed, hence starting with i = i - 1.
   * This is in case, stack was full before pushing all 1000 entries
  */
  k = i - 1;
  printf("Popping %d entries..\n", k);
  for (i = i - 1; i >= 1; i--) {
    if ((res = stack2_pop1(st, (void *)&elem))) {
      printf("Stack Test failed at %d. Stack1 is Empty! when not expected (err=%d)\n", i, res);
      test_status = 1;
      break;
    }
    if (i != elem) {
      printf("Stack Test failed at %d. Received %d but expected %d\n", i, elem, i);
      test_status = 1;
      break;
    }
    if ((res = stack2_pop2(st, (void *)&elem))) {
      printf("Stack Test failed at %d. Stack2 is Empty! when not expected (err=%d)\n", i, res);
      test_status = 1;
      break;
    }
    if (i != elem) {
      printf("Stack Test failed at %d. Received %d but expected %d\n", i, elem, i);
      test_status = 1;
      break;
    }
  }

  stack2_display(st, display_integer);
  //stack_test_empty_stack(st);

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  }

  return test_status;
}

int main()
{
  int test_status;
  stack2_t st;

  /* Initialize stack */
  st = stack2_create(256, 256, sizeof(int));

  /* Test 1: Verify 1000 Inserts and 1000 Deletes */
  test_status = stack2_test_1000(st);

  /* Test 2: Verify insert and delete 1000 times */
  //test_status = stack2_test_push_pop_1000(st);

  /* Destroy stack */
  stack2_destroy(st);

  return test_status;
}
