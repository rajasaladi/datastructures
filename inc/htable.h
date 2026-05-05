/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: htable.h                                                           *
 * Description: Defines interface for Hash Table Datastructure.               *
 * Created: Jun 2018                                                          *
*******************************************************************************
*/
#ifndef HTABLE_H
#define HTABLE_H
#include <err.h>

typedef struct htable_s *htable_t;

htable_t htable_create(int num_bins);
void htable_destroy(htable_t h);
int htable_insert(htable_t h, int key, int element);
void htable_delete(htable_t h, int key);
int htable_find(htable_t h, int key, int *pelement);
void htable_print(htable_t h);
int htable_increment(htable_t h, int key, int *pelement);

#endif /* HTABLE_H */
