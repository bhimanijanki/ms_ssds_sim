#ifndef HASH_H_
#define HASH_H_

#include <stdint.h>

#define HASH_SIZE                 104395303// 15485867 198491329 104395303  13807589

typedef struct hash_entry{
  int key;
  int counter;
  int value;
  uint64_t timestamp;             // last time this chunk was modified
  struct hash_entry *next;
}hash_entry_t;

typedef struct hash_table{
  int size;
  hash_entry_t **table;
}hash_table_t;

hash_table_t *hash_init(void);
int ht_hash(hash_table_t *hashtable, long int key);
hash_entry_t *ht_set(hash_table_t *hashtable, long int key);
hash_entry_t *ht_set_dict(hash_table_t *hashtable, long int key, int value);
hash_entry_t *ht_get(hash_table_t *hashtable, long int key);
hash_entry_t *ht_get_dict(hash_table_t *hashtable, long int key);


#endif
