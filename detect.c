#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "msssdsim.h"
#include "detect.h"

void cb_init(dev_meta_t *flash_meta)
{

  flash_meta->hashtable = hash_init();

}

int get_stream_id(dev_meta_t *flash_meta, request_t *req)
{
  // dummy stream id mapping
  // stream id 0 reserved for gc
  return (req->lba % flash_meta->total_multi_stream + 1);
}

int get_stream_id_lba_range(dev_meta_t *flash_meta, request_t *req)
{
  long int bucket_size = ADDRESS_RANGE / flash_meta->total_multi_stream;
  
  int stream_id = (int)(req->lba / bucket_size) + 1;

  if (stream_id > flash_meta->total_multi_stream)
    stream_id = flash_meta->total_multi_stream;
  return stream_id;
}

int get_stream_id_dict(dev_meta_t *flash_meta, request_t *req)
{
  int stream_id;
  //printf("good \n");
  stream_id = ht_get_dict(flash_meta->dict, (int)req->lba);
  if(stream_id>0 && stream_id<=16)
  {
  //printf("StreamID = %d\n", stream_id);
  //backup = stream_id;
    return stream_id;
  }
  return 0;
}

int get_stream_id_cb(dev_meta_t *flash_meta, request_t *req)
{
  hash_entry_t *entry = NULL;
  int chunk_num = req->lba / (CHUNK_SIZE_MB * 1024 * 1024 / 512);
  int stream_id = 0;
  static long int max_count;
  int count;

  entry = ht_get(flash_meta->hashtable, chunk_num);

  if (entry != NULL)
  {
    int count_per_stream = 0;
    // get stream id based on counter & pre-defined threshold
    // update the counter accordingly
    entry->counter++;
    count = entry->counter;
    if (count > max_count)
      max_count = count;

    count_per_stream = max_count / flash_meta->total_multi_stream;

    if (count_per_stream == 0)
      stream_id = 1;
    else
      stream_id = (count + count_per_stream - 1) / count_per_stream;

    if(stream_id > flash_meta->total_multi_stream)
      stream_id = flash_meta->total_multi_stream;
  }
  else
  {
    // create a new entry in hash and assign a stream id
    ht_set(flash_meta->hashtable, chunk_num);
    stream_id = 1;
    if (max_count == 0)
      max_count = 1;
  }

  //  printf("%d\n", stream_id);
  return stream_id;
}

int get_stream_id_cb2(dev_meta_t *flash_meta, request_t *req)
{
  /*
  int chunk_num = req->lba / (CHUNK_SIZE_MB * 1024 * 1024 / 512);
  int stream_id = 1;
  long int time_gap = 0;

  hash_entry_t *entry = NULL;

  long int score = 0;
  long int score_per_stream;
  static long int max_count;
  static long int max_time_gap;
  static stream_id_prev = 1;

  entry = ht_get(flash_meta->hashtable, chunk_num);

  if(entry != NULL)
  {
    // update the entry counter and timestamp
    // get stream id based on counter and time gap
    entry->counter++;
    time_gap = req->timestamp - entry->timestamp;
    if(time_gap < 0)
    {
      printf("time error current %ld last %ld\n", req->timestamp, entry->timestamp);
      exit(1);
    }
    else if(time_gap == 0) // same request
    {
      stream_id = stream_id_prev;

    }
    else
    {
      if(max_time_gap < time_gap)
	max_time_gap = time_gap;
      if(max_count < entry->counter)
	max_count = entry->counter;






      score = time_gap / entry->counter;
    if(score > max_score)
      max_score = score;

    score_per_stream = score / flash_meta->total_multi_stream;

    if (score_per_stream == 0)
      stream_id = 1;
    else{
      stream_id = (score + score_per_stream - 1) / score_per_stream;

      if(stream_id > flash_meta->total_multi_stream)
	stream_id = flash_meta->total_multi_stream;
      if(stream_id == 0)
	stream_id = 1;
    }
    entry->timestamp = req->timestamp;
  }
  else
  {
    // create a new entry in hash and assign a stream id
    entry = ht_set(flash_meta->hashtable, chunk_num);
    entry->timestamp = req->timestamp;
    stream_id = 1;
  }

  //  printf("stream id %d for block %ld time %ld\n", stream_id, req->lba, req->timestamp);
  return stream_id;
  */
  return 0;
}
