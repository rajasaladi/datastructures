/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: check_paranthesis.c                                                *
 * Description: Implements algorithm to check if paratheses match using stack *
 * Created: Jan 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stack.h>

void display_character(void *p)
{
  char *s;
  if (!p) return;

  s = (char *)p;
  printf(" %c", *s);
  return;
}

int check_paranthesis(char *s)
{
  char expected, actual;
  int match = 1, res;
  stack1_t st;

  if (!s) return 0;

  st = stack_create(512, sizeof(*s));
  while(*s) {
    switch(*s) {
      case '{':
      case '[':
      case '(':
        if((res = stack_push(st, (void *)s))) {
          printf("Stack push failed..(err=%d)\n", res);
          match = 0;
        }
        break;

      case '}':
      case ']':
      case ')':
        expected = ('}' == *s) ? '{' : ((']' == *s) ? '[' : '(');
        if ((res = stack_pop(st, (void *)&actual))) {
          //printf("Mismatch identifed, extra closing parantheses(err=%d)\n", res);
          match = 0;
          break;
        }

        if (actual != expected) {
          //printf("Mismatch identified..(expected=%c, actual=%c)\n", expected, actual);
          match = 0;
        }
        break;

      default:
      /* Do Nothing -- Ignore character */
        break;
    }

    /* Debug */
    //stack_custom_display(st, display_character);

    /* If mismatch or error encountered stop processing further */
    if (!match)
      break;

    s++;
  }

  /* If match is true and stack is not empty, mark it as mismatch */
  if(match && !stack_is_empty(st)) {
    //printf("Mismatch identified..unbalanced open parantheses\n");
    match = 0;
  }

  stack_destroy(st);

  return match;
}

int main()
{
  char buf[100];
  scanf("%s", buf);
  if (check_paranthesis(buf)) {
    printf("Parantheses Match!\n");
  }
  else {
    printf("Parantheses do NOT match\n");
  }

  return 0;
}
