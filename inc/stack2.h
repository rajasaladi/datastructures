/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: stack2.h                                                           *
 * Description: Defines interface for Datastructure with two stacks using one *
 *              array.                                                        *
 * Created: January, 2019                                                     *
*******************************************************************************
*/
#ifndef STACK2_H
#define STACK2_H
#include <err.h>

typedef void (* customfn_t)(void *);
/* Stack2 - Two Stack using (using One Array) */
typedef struct stack2_s *stack2_t;

stack2_t stack2_create(int stack_size1, int stack_size2, int elem_size);
void stack2_destroy(stack2_t st);
int stack2_push1(stack2_t st, void *pdata);
int stack2_pop1(stack2_t st, void *pdata);
int stack2_push2(stack2_t st, void *pdata);
int stack2_pop2(stack2_t st, void *pdata);
//void stack2_display(stack2_t st);
void stack2_display(stack2_t s, customfn_t fn);

#endif /* STACK2_H */
