/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: stack.h                                                            *
 * Description: Defines interface for Stack Datastructure.                    *
 * Created: January, 2019                                                     *
*******************************************************************************
*/
#ifndef STACK_H
#define STACK_H
#include <err.h>

typedef void (* customfn_t)(void *);
typedef struct stack1_s *stack1_t;
/*
 * NOTE:
 *   stack1_t is used for Stack type instead of stack_t as there exists
 *   another type named 'stack_t' for signal stack
 *   Refer to signal.h or _sigaltstack.h
*/

stack1_t stack_create(int stack_size, int elem_size);
void stack_destroy(stack1_t s);
int stack_push(stack1_t s, void *data);
int stack_pop(stack1_t s, void *data);
int stack_top(stack1_t s, void *data);
int stack_clear(stack1_t s);
int stack_is_empty(stack1_t s);
void stack_display(stack1_t s);
void stack_custom_display(stack1_t s, customfn_t fn);

#endif /* STACK_H */
