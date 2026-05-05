/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: htable.c                                                           *
 * Description: Implements Hash Table Data Structure.                         *
 * Created: Jun 2018                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <htable.h>

#define HTABLE_DEFAULT_BINS       10

typedef struct hnode_s hnode;
struct hnode_s {
  hnode *next;
  int key;
  int value;
};

/*
 * Hash Table
 * Hash Table maintains num_bins chains and
 * nodes within a chain are maintained in a sorted order.
 *
*/
struct htable_s {
  int num_bins;
  hnode **table;
};

/* Function: HTABLE_HASH
 * Description: Hash Function, which is modulo of total number of bins.
 * Input:
 * h - Hash Table
 * k - key
*/

/* Note:
 * Do not use abs() here as it does not work with INT_MIN i.e -2147483648
 * Ex: #define HTABLE_HASH(h, k)    (abs(k) % (h)->num_bins)
*/
#define HTABLE_HASH(h, k)    ((unsigned int)(k) % (h)->num_bins)

hnode *htable_find_internal(hnode *head, int key, hnode **pprev)
{
  hnode *p, *prev;

  p = head; prev = NULL;
  while(p) {
    if (key <= p->key) {
      p = (key == p->key) ? p : NULL;
      break;
    }
    prev = p;
    p = p->next;
  }

  if (pprev) {
    *pprev = prev;
  }

  return p;
}

htable_t htable_create(int num_bins)
{
  htable_t h = NULL;
  int i;

  num_bins = (num_bins <= 0) ? HTABLE_DEFAULT_BINS : num_bins;

  h = (htable_t)malloc(sizeof(struct htable_s) + num_bins * sizeof(hnode *));
  if (h) {
    h->num_bins = num_bins;
    h->table = (hnode **)(h + 1);
    for (i = 0; i < num_bins; i++) {
      h->table[i] = NULL;
    }
  }

  return h;
}

void htable_destroy(htable_t h)
{
  int i;
  hnode *p, *tmp;

  if (!h) return;

  if (h->table) {
    for (i = 0; i < h->num_bins; i++) {
      p = h->table[i];
      while(p) {
        tmp = p;
        p = p->next;
        free(tmp);
      }
    }
  }

  free(h);

  return;
}

/* Function: htable_insert
 * Description: Inserts a key into hashtable
 * Input:
 * h - Hash table
 * key - Key to be inserted
 *
 * Return
 * Returns count for the number of times the key was inserted
*/
int htable_insert(htable_t h, int key, int element)
{
  int i;
  hnode *p, *prev = NULL;

  if (!h || !h->table) return EBADPARM;

  i = HTABLE_HASH(h, key);

  p = htable_find_internal(h->table[i], key, &prev);

  if (p) {
    return EEXISTS;
  }

  p = (hnode *)malloc(sizeof(hnode));
  if (!p) {
    return ENOMEMORY;
  }

  p->key = key;
  p->value = element;
  if (prev) {
    p->next = prev->next;
    prev->next = p;
  } else {
    p->next = h->table[i];
    h->table[i] = p;
  }

  return EOK;
}

/* Function: htable_increment
 * Description:
 *   Increments value at key. If key, doesn't exist then
 *   the key is inserted into hash table with value 1.
 * Input:
 * h - Hash table
 * key - Key to be inserted
 * pelement - place holder to return the new value.
 *
 * Return
 *   Returns count for the number of times the key was inserted
*/
int htable_increment(htable_t h, int key, int *pelement)
{
  int i;
  hnode *p, *prev = NULL;

  if (!h || !h->table) return EBADPARM;

  i = HTABLE_HASH(h, key);

  p = htable_find_internal(h->table[i], key, &prev);

  if (p) {
    p->value++;
  }
  else {
    p = (hnode *)malloc(sizeof(hnode));
    if (!p) {
      return ENOMEMORY;
    }
    p->key = key;
    p->value = 1;
    if (prev) {
      p->next = prev->next;
      prev->next = p;
    } else {
      p->next = h->table[i];
      h->table[i] = p;
    }
  }

  if (pelement) {
    *pelement = p->value;
  }

  return EOK;
}

/* Function: htable_delete
 * Description: Deletes a key from hashtable
 * Input:
 * h - Hash table
 * key - Key to be deleted
 *
 * Return:
 *   None
*/
void htable_delete(htable_t h, int key)
{
  int i;
  hnode *p, *prev = NULL;

  if (!h || !h->table) {
    printf("Delete: Invalid hash table\n");
    return;
  }

  i = HTABLE_HASH(h, key);

  p = htable_find_internal(h->table[i], key, &prev);

  if (!p) {
    printf("Delete (%d): Entry NOT found!\n", key);
    return;
  }

  if (prev) {
    prev->next = p->next;
  } else {
    h->table[i] = p->next;
  }

  free(p);

  return;
}

/* Function: htable_find
 * Description: Returns the value for a given key from hashtable
 * Input:
 * h - Hash table
 * key - Key
 *
 * Return:
 *   None
*/
int htable_find(htable_t h, int key, int *pelement)
{
  int i;
  hnode *p;

  if (!h || !h->table ||pelement) return EBADPARM;

  i = HTABLE_HASH(h, key);

  p = htable_find_internal(h->table[i], key, NULL);

  if (!p) {
    return ENOTEXIST;
  }

  *pelement = p->value;

  return EOK;
}

void htable_print(htable_t h)
{
  int i, count = 0;
  hnode *p;

  if (!h || !h->table) {
    printf("Hash Table is Empty!\n");
    return;
  }

  for (i = 0; i < h->num_bins; i++) {
    if (h->table[i]) {
      count++;
      printf("Bin%d", i);
      p = h->table[i];
      while(p) {
        //printf(" - %d,%d", p->key, p->value);
        printf(" -> [%d,%d]", p->key, p->value);
        p = p->next;
      }
      printf("\n");
    }
#if 0
    else {
      printf("Bin%d -\n", i);
    }
#endif
  }

  if (!count) {
    printf("Hash Table is Empty!\n");
  }

  return;
}
