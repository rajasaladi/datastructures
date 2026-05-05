/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: disjset_test.c                                                     *
 * Description: Implements Test module to test Disjoint Set Data Structure.   *
 * Created: Jul 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <disjset.h>

int disjset_test_union_find(disjset_t set, int num)
{
  int i, a, b, test_status = 0;

  printf("\nEven-Odd test case starting..\n");

  for (i = 0; i < num; i += 2) {
    disjsetUnion(set, 0, i);
  }

  for (i = 1; i < num; i += 2) {
    disjsetUnion(set, 1, i);
  }
  disjsetPrint(set);

  for (i = 0; i < num; i += 2) {
    if ((a = disjsetFind(set, 0)) != (b = disjsetFind(set, i))) {
      printf("Test failed at %d (%d), %d (%d) ..\n", 0, a, i, b);
      test_status = 1;
      break;
    }
  }

  for (i = 1; i < num; i += 2) {
    if ((a = disjsetFind(set, 1)) != (b = disjsetFind(set, i))) {
      printf("Test failed at %d (%d), %d (%d) ..\n", 1, a, i, b);
      test_status = 1;
      break;
    }
  }

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  }

  return test_status;
}

int disjset_test_union_find_random(disjset_t set, int num)
{
  int i, num1, num2, a, b, test_status = 0;
  int s1[] = {4, 8, 21, 19, 36, 48, 13, 27, 91};
  int s2[] = {46, 28, 96, 76, 81, 94, 22, 6, 18};

  printf("\nRandom 2 set test case starting..\n");

  num1 = sizeof(s1)/sizeof(s1[0]);
  for (i = 1; i < num1; i++) {
    disjsetUnion(set, s1[i - 1], s1[i]);
  }

  num2 = sizeof(s2)/sizeof(s2[0]);
  for (i = 1; i < num2; i++) {
    disjsetUnion(set, s2[i - 1], s2[i]);
  }

  disjsetPrint(set);

  for (i = 1; i < num1; i++) {
    if ((a = disjsetFind(set, s1[i - 1])) != (b = disjsetFind(set, s1[i]))) {
      printf("Test failed at %d (%d), %d (%d) ..\n", i - 1, a, i, b);
      test_status = 1;
      break;
    }
  }

  for (i = 1; i < num2; i++) {
    if ((a = disjsetFind(set, s2[i - 1])) != (b = disjsetFind(set, s2[i]))) {
      printf("Test failed at %d (%d), %d (%d) ..\n", i - 1, a, i, b);
      test_status = 1;
      break;
    }
  }

  if (!test_status) {
    printf("Test Passed Successfully!\n");
  }

  return test_status;
}

int main()
{
  int test_status;
  int num;
  disjset_t set;

  num = 100;
  set = disjsetCreate(num);
  if (!set) return -1;
  //printf("Disjoint Set created..\n");

  test_status = disjset_test_union_find(set, num);
  disjsetDestroy(set);
  //printf("Disjoint Set destroyed..\n");


  set = disjsetCreate(num);
  if (!set) return -1;
  //printf("Disjoint Set created..\n");

  test_status = disjset_test_union_find_random(set, num);
  disjsetDestroy(set);
  //printf("Disjoint Set destroyed..\n");

  return 0;
}
