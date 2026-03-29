/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: stack_test.c                                                       *
 * Description: Implements Test module to test Stack Data Structure.          *
 * Created: January, 2019                                                     *
*******************************************************************************
*/
#include <stdio.h>
#include <stack.h>

void stack_test_empty_stack(stack1_t s)
{
  int elem;

  while (!stack_pop(s, (void *)&elem))
    ;

  return;
}

int stack_test_1000(stack1_t s)
{
  int i, k, elem, res, test_status = 0; /* SUCCESS */

  printf("Stack Test 1: Verify 1000 pushs and 1000 pops\n");
  printf("Pushing 1000 entries..\n");
  for (i = 1; i <= 1000; i++) {
    if ((res = stack_push(s, (void *)&i))) {
      printf("Stack is full at %d (err=%d)\n", i, res);
      break;
    }
  }

  stack_display(s);

  /* Pop only the entries pushed, hence starting with i = i - 1.
   * This is in case, stack was full before pushing all 1000 entries
  */
  k = i - 1;
  printf("Popping %d entries..\n", k);
  for (i = i - 1; i >= 1; i--) {
    if ((res = stack_pop(s, (void *)&elem))) {
      printf("Stack Test failed at %d. Stack is Empty! when not expected (err=%d)\n", i, res);
      test_status = 1;
      break;
    }
    if (i != elem) {
      printf("Stack Test failed at %d. Received %d but expected %d\n", i, elem, i);
      test_status = 1;
      break;
    }
  }

  stack_display(s);
  stack_test_empty_stack(s);

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  }

  return test_status;
}

int stack_test_push_pop_1000(stack1_t s)
{
  int i, elem, res, test_status = 0; /* SUCCESS */

  printf("Stack Test 2: Verify push followed by pop 1000 times\n");
  for (i = 1; i <= 1000; i++) {
    if ((res = stack_push(s, (void *)&i))) {
      printf("Stack test failed at %d. Stack is Full, when not expected! (err=%d)\n", i, res);
      test_status = 1;
      break;
    }
    stack_display(s);
    if ((res = stack_pop(s, (void *)&elem))) {
      printf("Stack test failed at %d. Stack is Empty, when not expected! (err=%d)\n", i, res);
      test_status = 1;
      break;
    }
    if (i != elem) {
      printf("Stack test failed at %d. Received %d but expected %d\n", i, elem, i);
      test_status = 1;
      break;
    }
  }

  stack_display(s);
  stack_test_empty_stack(s);

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  }

  return test_status;
}

int main()
{
  int test_status;
  stack1_t st;

  /* Initialize stack1 */
  st = stack_create(512, sizeof(int));

  /* Test 1: Verify 1000 Inserts and 1000 Deletes */
  test_status = stack_test_1000(st);

  /* Test 2: Verify insert and delete 1000 times */
  test_status = stack_test_push_pop_1000(st);

  /* Destroy stack */
  stack_destroy(st);

  return test_status;
}
