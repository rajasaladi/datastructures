/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: disjset.h                                                          *
 * Description: Defines interface for Disjoint Set Datastructure.             *
 * Created: Jul 2019                                                          *
*******************************************************************************
*/
#ifndef DISJSET_H
#define DISJSET_H
#include <err.h>

typedef struct disjset_s *disjset_t;

disjset_t disjsetCreate(int num);
void disjsetDestroy(disjset_t s);
int disjsetUnion(disjset_t s, int a, int b);
int disjsetFind(disjset_t s, int a);
void disjsetPrint(disjset_t s);

#endif /* DISJSET_H */
