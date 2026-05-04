/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: queue.h                                                            *
 * Description: Defines interface for Queue Datastructure.                    *
 * Created: Jul 2019                                                          *
*******************************************************************************
*/
#ifndef QUEUE_H
#define QUEUE_H
#include <err.h>

typedef void (*queue_dispfn_t)(void *);
typedef struct queue_s *queue_t;

queue_t queue_create(int queue_size, int elem_size);
void queue_destroy(queue_t q);
int queue_enqueue(queue_t q, void *data);
int queue_dequeue(queue_t q, void *data);
int queue_length(queue_t q);
void queue_display(queue_t q, queue_dispfn_t fn);

#endif /* QUEUE_H */
