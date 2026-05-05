/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: trie.h                                                             *
 * Description: Defines interface for Trie Datastructure.                     *
 * Created: Jul 2019                                                          *
*******************************************************************************
*/
#ifndef TRIE_H
#define TRIE_H

#include <err.h>

typedef struct trie_s *trie_t;

trie_t trie_create(void);
void trie_destroy(trie_t t);
int trie_find(trie_t t, char *word);
int trie_find_prefix(trie_t t, char *prefix);
int trie_add(trie_t t, char *word);
void trie_delete(trie_t t, char *word);
int trie_num_words(trie_t t);
void trie_print(trie_t t);

#endif /* TRIE_H */
