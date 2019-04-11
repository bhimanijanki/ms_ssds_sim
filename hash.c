#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

hash_table_t *hash_init(void)
{
  int i;
  hash_table_t *hashtable;
  if((hashtable = malloc(sizeof(hash_table_t))) == NULL)
  {
    printf("failed to allocate hash table\n"); 
    exit(1);
  }

  if((hashtable->table = malloc(sizeof(hash_entry_t *) * HASH_SIZE)) == NULL)
  {
    printf("failed to allocate hash entries\n");
    exit(1);
  }

  for(i = 0; i < HASH_SIZE; i++)
  {
    hashtable->table[i] = NULL; 
  }
  hashtable->size = HASH_SIZE;

  return hashtable;
}


int ht_hash(hash_table_t *hashtable, long int key)
{
  return key % hashtable->size;
}

hash_entry_t *ht_newpair(long int key)
{
  hash_entry_t *newentry;

  if((newentry = malloc(sizeof(hash_entry_t))) == NULL)
  {
    printf("failed to allocate new hash entry\n");
    exit(1);
  }

    newentry->key = key;
    newentry->counter = 1;
    newentry->next = NULL;

    return newentry;
}

hash_entry_t *ht_set_dict(hash_table_t *hashtable, long int key, int value)
{
  hash_entry_t *new = NULL;
  hash_entry_t *next = NULL;
  hash_entry_t *prev = NULL;
  hash_entry_t *result = NULL;

  int bucket = 0;

  bucket = ht_hash(hashtable, key);

  next = hashtable->table[bucket];

  while(next != NULL && next->key != key)
  {
    prev = next;
    next = next->next;
  }

  // There is already an entry, update it
  if(next != NULL && next->key == key)
  {
    //Increment the counter by 1
    next->value = value;
    result = next;
  }
  else // No existing entry, insert a new one
  {
    new = ht_newpair(key);
    new->key=key;
    new->value=value;
    // at the start of the linked list
    if(next == hashtable->table[bucket])
    {
      new->next = next;
      hashtable->table[bucket] = new;
    } 
    else if (next == NULL) // at the end of the list
    {
      prev->next = new;
    } 
    else  // in the middle of the list
    {
      new->next = next;
      prev->next = new;
    }
    result = new;
  }
  return result->value;
}

hash_entry_t *ht_set(hash_table_t *hashtable, long int key)
{
  hash_entry_t *new = NULL;
  hash_entry_t *next = NULL;
  hash_entry_t *prev = NULL;
  hash_entry_t *result = NULL;

  int bucket = 0;

  bucket = ht_hash(hashtable, key);

  next = hashtable->table[bucket];

  while(next != NULL && next->key != key)
  {
    prev = next;
    next = next->next;
  }

  // There is already an entry, update it
  if(next != NULL && next->key == key)
  {
    //Increment the counter by 1
    next->counter++;
    result = next;
  }
  else // No existing entry, insert a new one
  {
    new = ht_newpair(key);

    // at the start of the linked list
    if(next == hashtable->table[bucket])
    {
      new->next = next;
      hashtable->table[bucket] = new;
    } 
    else if (next == NULL) // at the end of the list
    {
      prev->next = new;
    } 
    else  // in the middle of the list
    {
      new->next = next;
      prev->next = new;
    }
    result = new;
  }
  return result;
}

hash_entry_t *ht_get(hash_table_t *hashtable, long int key)
{
  int bucket = ht_hash(hashtable, key);

  hash_entry_t *result;

  result = hashtable->table[bucket];
  while(result != NULL && result->key != key)
  {
    result = result->next;
  }

  if(result != NULL && result->key == key)
    return result;
  else
    return NULL;

}

hash_entry_t *ht_get_dict(hash_table_t *hashtable, long int key)
{
  int bucket = ht_hash(hashtable, key);

  hash_entry_t *result;

  result = hashtable->table[bucket];
  while(result != NULL && result->key != key)
  {
    result = result->next;
  }

  if(result != NULL && result->key == key)
    return result->value;
  else
    return NULL;

}
