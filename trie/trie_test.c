#include <stdio.h>
#include <trie.h>

char *strings1[] = {
  "apple", "amazon", "google", "facebook", "intel", "qualcomm",
};

char *strings2[] = {
  "a", "app", "apple", "apples", "apartment", "apply", "apollo",
};

int main(void)
{
  int i, num1, num2;
  trie_t t;

  t = trie_create();
  if (!t) {printf("Trie create failed\n"); return 1;}

  num1 = sizeof(strings1)/sizeof(strings1[0]);
  printf("Adding %d strings1..\n", num1);
  for (i = 0; i < num1; i++) {
    trie_add(t, strings1[i]);
  }
  trie_print(t);

  printf("Deleting %s ..\n", strings1[5]);
  trie_delete(t, strings1[5]);
  trie_print(t);

  printf("Adding %s ..\n", strings1[5]);
  trie_add(t, strings1[5]);
  trie_print(t);

  printf("Adding %s again ..\n", strings1[5]);
  trie_add(t, strings1[5]);
  trie_print(t);

  printf("Adding qualcommm ..\n");
  trie_add(t, "qualcommm");
  trie_print(t);

  printf("Deleting qualcommm ..\n");
  trie_delete(t, "qualcommm");
  trie_print(t);

  printf("Deleting all strings1..\n");
  for (i = 0; i < num1; i++) {
    trie_delete(t, strings1[i]);
  }
  trie_print(t);

  printf("Adding the strings1 back..\n");
  for (i = 0; i < num1; i++) {
    trie_add(t, strings1[i]);
  }
  trie_print(t);

  printf("Deleting all strings1..\n");
  for (i = 0; i < num1; i++) {
    trie_delete(t, strings1[i]);
  }
  trie_print(t);

  num2 = sizeof(strings2)/sizeof(strings2[0]);
  printf("Adding strings2 ..\n");
  for (i = 0; i < num2; i++) {
    trie_add(t, strings2[i]);
  }
  trie_print(t);

  printf("Adding the strings1 back..\n");
  for (i = 0; i < num1; i++) {
    trie_add(t, strings1[i]);
  }
  trie_print(t);

  trie_destroy(t);

  return 0;
}
