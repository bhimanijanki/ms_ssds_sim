#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdint.h>

#define TOTAL_FLASH_SIZE_SECTOR     1024
#define EB_SIZE_IN_SECTOR           409600 //204800   // 100MB
#define BUCKET_SIZE                6757507    //1301081//104395303//86028121    // 1301081
#define GC_CYCLE                    1
#define GC_THRESHOLD                5


typedef struct run_stats{
  uint64_t req_total;
  uint64_t req_write;
  uint64_t req_read;
  uint64_t req_write_sectors;
  uint64_t req_read_sectors;
  uint64_t total_erase_count;
  uint64_t total_sectors_gc_copied;
  uint64_t *multi_stream_io;
}run_stats_t;

typedef struct forward_map{
  uint64_t lba;
  uint64_t addr;
  struct forward_map *next;
}forward_map_t;

typedef struct eb_meta{
  int eb_id;
  //int free_num_sectors;
  uint64_t valid_num_sectors;
  int erase_count;
  uint64_t curr_write_pos;
  struct eb_meta *next;
  struct eb_meta *prev;
}eb_meta_t;

typedef struct multi_stream{
  int curr_open_s_num;
  eb_meta_t **curr_open_eb;
}multi_stream_t;

typedef struct request {
  uint64_t timestamp;
  uint64_t lba;
}request_t;

typedef struct dev_meta{
  int total_logical_eb;
  int free_num_eb;
  int gc_threshold;
  int total_multi_stream;
  eb_meta_t *curr_eb;
  eb_meta_t *curr_gc_eb;
  eb_meta_t *freelist_head;
  eb_meta_t *freelist_tail;
  eb_meta_t *finish_list;
  uint64_t  *rev_map;
  forward_map_t **index;
  eb_meta_t **logical_eb_list;
  run_stats_t *stats;
  multi_stream_t *ms_meta;
  int (*getid_fnc)(struct dev_meta*, request_t *req);
  hash_table_t *hashtable;
  hash_table_t *dict;
}dev_meta_t;


#endif
