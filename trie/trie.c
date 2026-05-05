/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: trie.c                                                             *
 * Description: Implements Trie Data Structure.                               *
 * Created: Jul 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <trie.h>

#define NUMCHILD      26
typedef struct tnode_s tnode;

struct tnode_s {
  int isWord;
  tnode *child[NUMCHILD];
};

struct trie_s {
  tnode *root;
  int numWords;
};

/******************************************************************************
 *                    P R I V A T E   F U N C T I O N S                       *
 ******************************************************************************
*/

/*
 * Function
 * Name: trie_find_internal
 * Description: Core function used to traverse trie and find the node for a given word.
 * Params:
 *   p - pointer to root node of the trie.
 *   word - word to be found.
 *   pparent - double pointer to return parent of the node found.
 * Return:
 *   Returns the pointer to the node found.
 *
*/
static tnode *trie_find_internal(tnode *p, char *word, tnode **pparent)
{
  int i, j;
  tnode *parent;

  parent = NULL;

  for (i = 0; '\0' != word[i] && p; i++) {
    parent = p;
    p = p->child[word[i] - 'a'];
  }
  if (pparent) *pparent = parent;

  return p;
}

/*
 * Function
 * Name: trie_free
 * Description: Recursively free all sub tries and then free the node itself.
 * Params:
 *   p - pointer to root node of the trie.
 * Return:
 *   None
 *
*/
static void trie_free(tnode *p)
{
  int i;

  if (!p) return;

  for (i = 0; i < NUMCHILD; i++) {
    trie_free(p->child[i]);
  }
  free(p);

  return;
}

/******************************************************************************
 *                      P U B L I C   F U N C T I O N S                       *
 ******************************************************************************
*/
/*
 * Function
 * Name: trie_create
 * Description: Allocates and initializes the Trie data structure.
 * Params: None
 * Return:
 *   Returns the pointer to allocated Trie data structure.
 *
*/
trie_t trie_create(void)
{
  trie_t t;

  t = (trie_t)malloc(sizeof(struct trie_s));
  if (!t) return NULL;

  t->root = (tnode *)calloc(1, sizeof(tnode));
  if (!t->root) {free(t); return NULL;}
  t->numWords = 0;

  return t;
}

/*
 * Function
 * Name: trie_destroy
 * Description: De-Allocates the Trie data structure.
 * Params:
 *   t - Trie
 * Return: None
 *
*/
void trie_destroy(trie_t t)
{
  if (!t) return;

  trie_free(t->root);
  free(t);

  return;
}

/*
 * Function
 * Name: trie_find
 * Description: Finds for a word in the Trie.
 * Params:
 *   t - Trie
 *   word - word to be searched
 * Return:
 *   EOK if exists or
 *   ENOTEXIST if the word doesn't exist.
 *   error code in case of any error.
 *
*/
int trie_find(trie_t t, char *word)
{
  tnode *p;

  if (!t || !word) return EBADPARM;

  p = trie_find_internal(t->root, word, NULL);

  return (p && p->isWord) ? EOK : ENOTEXIST;
}

/*
 * Function
 * Name: trie_find_prefix
 * Description: Finds if a prefix exists in the Trie.
 * Params:
 *   t - Trie
 *   prefix - prefix to be searched
 * Return:
 *   EOK if exists or
 *   ENOTEXIST if the word doesn't exist.
 *   error code in case of any error.
 *
*/
int trie_find_prefix(trie_t t, char *prefix)
{
  tnode *p;

  if (!t || !prefix) return EBADPARM;

  p = trie_find_internal(t->root, prefix, NULL);

  return (p) ? EOK : ENOTEXIST;
}

/*
 * Function
 * Name: trie_add
 * Description: Adds a word to the Trie.
 * Params:
 *   t - Trie
 *   word - word to be added
 * Return: EOK or error code.
 *
*/
int trie_add(trie_t t, char *word)
{
  int i, j;
  tnode *p;

  if (!t || !word) return EBADPARM;

  p = t->root;
  for (i = 0; '\0' != word[i]; i++) {
    j = word[i] - 'a';
    if (!p->child[j]) {
      p->child[j] = (tnode *)calloc(1, sizeof(tnode));
      if (!p->child[j]) return ENOMEMORY;
    }
    p = p->child[j];
  }

  if (!p->isWord) {
    p->isWord = 1;
    t->numWords++;
  }

  return EOK;
}

/*
 * Function
 * Name: trie_delete
 * Description: Deletes a word from the Trie.
 * Params:
 *   t - Trie
 *   word - word to be deleted
 * Return:
 *   None
 *
*/
void trie_delete(trie_t t, char *word)
{
  tnode *p;

  if (!t || !word) return;

  p = trie_find_internal(t->root, word, NULL);
  if (p && p->isWord) {
    p->isWord = 0;
    t->numWords--;
  }

  return;
}

/*
 * Function
 * Name: trie_num_words
 * Description: Gets the number of words in the Trie.
 * Params:
 *   t - Trie
 * Return:
 *   Returns the number of words in the Trie.
 *
*/
int trie_num_words(trie_t t)
{
  return (t) ? t->numWords : 0;
}

static int trie_depth_rec(tnode *p)
{
  int i, d, max = -1;

  if (!p) return -1;

  for (i = 0; i < NUMCHILD; i++) {
    d = trie_depth_rec(p->child[i]);
    if (d > max) max = d;
  }

  return max + 1;
}

/*
 * Function
 * Name: trie_depth
 * Description: Gets the depth of the Trie.
 * Params:
 *   t - Trie
 * Return:
 *   Returns the depth of the Trie.
 *
*/
int trie_depth(trie_t t)
{
  if (!t) return 0;
  return trie_depth_rec(t->root);
}

static void trie_print_rec(tnode *p, char *s, int index)
{
  int i;

  if (!p) return;

  if (p->isWord) {
    s[index] = '\0';
    printf("%s\n", s);
  }

  for (i = 0; i < NUMCHILD; i++) {
    s[index] = 'a' + i;
    trie_print_rec(p->child[i], s, index + 1);
  }

  return;
}

/*
 * Function
 * Name: trie_print
 * Description: Prints the Trie
 * Params:
 *   t - Trie
 * Return:
 *   None
 *
*/
void trie_print(trie_t t)
{
  char *s;
  int d;

  if (!t) return;

  if (!t->numWords) {printf("Trie: empty!\n\n"); return;}

  d = trie_depth(t);
  s = (char *)malloc(d + 1);
  if (!s) return;

  printf("Trie (%d):\n", t->numWords);
  trie_print_rec(t->root, s, 0);
  printf("\n");

  free(s);

  return;
}
