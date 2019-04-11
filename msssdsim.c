#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>

#include "hash.h"
#include "msssdsim.h"
#include "detect.h"

void usage(char *program)
{
  printf("usage: %s -f trace_file -s flash_size [-m #_streams] [-c detect_alg] [r]\n", program);
  printf("-f      trace_file   :  MSR trace format\n");
  printf("-d      dict_file   :  LBA , STREAM ID\n");
  printf("-s      flash_size   :  flash size in 512byte sectors\n");
  printf("-m      #_streams    :  number of streams\n");
  printf("-c      detect_alg   :  detection algorithm\n");
  printf("-r                   :  consider 'read' as 'write' in the first loop\n");
}

void print_stats(dev_meta_t *flash_meta)
{
  uint64_t total_req = flash_meta->stats->req_total;
  uint64_t total_write_sectors = flash_meta->stats->req_write_sectors;
  uint64_t total_gc_write = flash_meta->stats->total_sectors_gc_copied;
  int i;

  float WA = ((float)total_write_sectors + (float)total_gc_write) / (float)total_write_sectors;

  printf("============ \n");
  printf("%ld %ld %ld %ld %.2f\n",total_req, total_write_sectors, total_gc_write, flash_meta->stats->total_erase_count, WA);

  if(flash_meta->stats->multi_stream_io)
  {
    for (i = 0; i < flash_meta->total_multi_stream + 1; i++)
      printf("%ld " , flash_meta->stats->multi_stream_io[i]);

    printf("\n");
  }

}

void print_free_eb_stats(dev_meta_t *flash_meta)
{
  eb_meta_t *eb = flash_meta->freelist_head;
  while(eb != NULL)
  {
    printf("eb id %d\n", eb->eb_id);
    eb = eb->next;
  }
}

void insert_to_freelist_head(dev_meta_t *flash_meta, eb_meta_t *eb)
{
  if (flash_meta->freelist_head == NULL)
  {
    flash_meta->freelist_head = eb;
    flash_meta->freelist_tail = eb;
  }
  else
  {
    eb->next = flash_meta->freelist_head;
    flash_meta->freelist_head->prev = eb;
    flash_meta->freelist_head = eb;
  }
}

void insert_to_finishlist_head(dev_meta_t *flash_meta, eb_meta_t *eb)
{
  if (flash_meta->finish_list == NULL)
  {
    flash_meta->finish_list = eb;
  }
  else
  {
    eb->next = flash_meta->finish_list;
    flash_meta->finish_list = eb;
  }
}

void extract_from_finish_list(dev_meta_t *flash_meta, eb_meta_t *eb_delete)
{
  eb_meta_t *tmp, *prev;

  if(flash_meta->finish_list == NULL || eb_delete == NULL)
    return;

  if(flash_meta->finish_list == eb_delete)
  {
    flash_meta->finish_list = eb_delete->next;
  }
  else
  {
    prev = flash_meta->finish_list;
    tmp = prev->next;
    while(tmp)
    {
      if(tmp == eb_delete)
      {
	prev->next = tmp->next;
	tmp->next = NULL;
	break;
      }
      tmp = tmp->next;
      prev = prev->next;
    }
  }
} 

eb_meta_t *extract_from_freelist_tail(dev_meta_t *flash_meta)
{
  eb_meta_t *free_eb = NULL;
  if (flash_meta->freelist_tail == NULL)
  {
    printf("No more free eb in the list\n");
    return NULL;
  }
  else
  {
    free_eb = flash_meta->freelist_tail;
    if (flash_meta->freelist_tail == flash_meta->freelist_head)
    {
      flash_meta->freelist_tail = NULL;
      flash_meta->freelist_head = NULL;
    }
    else
    {
      flash_meta->freelist_tail = free_eb->prev;
      flash_meta->freelist_tail->next = NULL;
    }
  }

  free_eb->next = NULL;
  free_eb->prev = NULL;

  return free_eb;
}

void flash_init(dev_meta_t *flash_meta, int flash_size, int multi_stream_on, int clustering_alg)
{
  int i;

  flash_meta->total_logical_eb = flash_size / EB_SIZE_IN_SECTOR;
  flash_meta->free_num_eb = flash_meta->total_logical_eb;
  flash_meta->gc_threshold = GC_THRESHOLD;
  flash_meta->total_multi_stream = multi_stream_on;
  flash_meta->finish_list = NULL;
  flash_meta->freelist_head = NULL;
  flash_meta->freelist_tail = NULL;
  flash_meta->curr_eb = NULL;  
  flash_meta->curr_gc_eb = NULL;

  flash_meta->rev_map = malloc(flash_size * sizeof(uint64_t));
  memset(flash_meta->rev_map, 0, flash_size * sizeof(uint64_t));

  flash_meta->index = malloc(BUCKET_SIZE * sizeof(forward_map_t *));
  memset(flash_meta->index, 0, BUCKET_SIZE * sizeof(forward_map_t *));

  flash_meta->stats = malloc(sizeof(run_stats_t));
  memset(flash_meta->stats, 0, sizeof(run_stats_t));

  if (multi_stream_on > 0)
    flash_meta->stats->multi_stream_io = malloc(sizeof(uint64_t) * multi_stream_on);
  else
    flash_meta->stats->multi_stream_io = NULL;

  switch(clustering_alg){
  case DETECTION_DUMMY:
    flash_meta->getid_fnc = &get_stream_id;
    break;
  case DETECTION_LBA_RANGE:
    flash_meta->getid_fnc = &get_stream_id_lba_range;
    break;
  case DETECTION_CB:
    flash_meta->getid_fnc = &get_stream_id_cb;
    break;
  case DETECTION_CB2:
    flash_meta->getid_fnc = &get_stream_id_cb2;
    break;
  case DETECTION_DICT:
    flash_meta->getid_fnc = &get_stream_id_dict;
    break;
  }

  if(flash_meta->total_multi_stream > 0 && (clustering_alg == DETECTION_CB || clustering_alg == DETECTION_CB2))
  {
    cb_init(flash_meta);
  }

  flash_meta->logical_eb_list = malloc(flash_meta->total_logical_eb * sizeof(eb_meta_t*));
  for (i = 0; i < flash_meta->total_logical_eb; i++)
  {
    eb_meta_t *eb_metadata = malloc(sizeof(eb_meta_t));
    flash_meta->logical_eb_list[i] = eb_metadata;
    eb_metadata->eb_id = i;
    //    eb_metadata->free_num_sectors = EB_SIZE_IN_SECTOR;
    eb_metadata->valid_num_sectors = 0;
    eb_metadata->erase_count = 0;
    eb_metadata->curr_write_pos = 0;
    eb_metadata->next = NULL;
    eb_metadata->prev = NULL;
    insert_to_freelist_head(flash_meta, eb_metadata);
  }

  if (flash_meta->total_multi_stream == 0)
  {
    // multi_stream feature is off
    // get one free eb at initialization
    flash_meta->curr_eb = extract_from_freelist_tail(flash_meta); 
    flash_meta->free_num_eb--;
  }
  else
  {
    flash_meta->ms_meta = malloc(sizeof(multi_stream_t));
    flash_meta->ms_meta->curr_open_s_num = 0;
    flash_meta->ms_meta->curr_open_eb = malloc((multi_stream_on + 1) * sizeof(eb_meta_t *));
    memset(flash_meta->ms_meta->curr_open_eb, 0, (multi_stream_on + 1) * sizeof(eb_meta_t*));
  }
  //print_free_eb_stats(flash_meta);
}

// Greedy policy
eb_meta_t * get_victim_eb(dev_meta_t *flash_meta)
{
  eb_meta_t *tmp = flash_meta->finish_list;
  eb_meta_t *victim_eb = tmp;

  uint64_t min_valid_sectors;

  if (flash_meta->finish_list == NULL)
  {
    printf("No candidate eb for gc\n");
    return NULL;
  }

  min_valid_sectors = tmp->valid_num_sectors;

  while (tmp)
  {
    if (tmp->valid_num_sectors <= min_valid_sectors && tmp->valid_num_sectors < EB_SIZE_IN_SECTOR)
    {
      min_valid_sectors = tmp->valid_num_sectors;
      victim_eb = tmp;
    }
    tmp = tmp->next;
  }

  if (min_valid_sectors == EB_SIZE_IN_SECTOR)
  {
    printf("No candidat for gc -- all data is valid\n");
    return NULL;
  }

  //  printf("eb %d is selected -- %ld valid sectors\n", victim_eb->eb_id, victim_eb->valid_num_sectors);
  return victim_eb;
}

int write_to_eb(dev_meta_t *flash_meta, request_t *req, int is_gc_write, int prev_stream_id);
int do_write_to_eb_ms(dev_meta_t *flash_meta, request_t *req, int is_gc_write, int prev_stream_id);
void gc_run(dev_meta_t *flash_meta, int prev_stream_id)
{
  int i;
  assert(flash_meta->curr_gc_eb == NULL);
  request_t *req = malloc(sizeof(request_t));

  for (i = 0; i < GC_CYCLE; i++)
  {
    //    printf("----- round %d of gc\n", i);
    flash_meta->curr_gc_eb = get_victim_eb(flash_meta);
    if (flash_meta->curr_gc_eb == NULL) 
    { 
      if(flash_meta->free_num_eb * 100 / flash_meta->gc_threshold <= flash_meta->total_logical_eb)
      {
	printf("No more gc candidate, not enough space\n");
	exit(1);
      }
      else
      {
	printf("done with this gc path");
	break;  // done with this gc path
      }
    }
    //do real gc work
    if (flash_meta->curr_gc_eb->valid_num_sectors > 0)
    {
      for (i = 0; i < EB_SIZE_IN_SECTOR; i++)
      {
        int start_eb_offset = flash_meta->curr_gc_eb->eb_id * EB_SIZE_IN_SECTOR;
        if(flash_meta->rev_map[start_eb_offset + i] == -1)
        {
	  //printf("address %ld is invalid\n", flash_meta->rev_map[start_eb_offset + i]);
	  continue;
        }

	req->lba = flash_meta->rev_map[start_eb_offset + i];
        //printf("address %ld is valid\n", flash_meta->rev_map[start_eb_offset + i]);
	prev_stream_id = write_to_eb(flash_meta, req, 1, prev_stream_id);
        flash_meta->stats->total_sectors_gc_copied++;
      }
    }

    // done with this eb cleaning, reset eb metadata
    // remove from finish list, put to free list
    assert(flash_meta->curr_gc_eb->valid_num_sectors == 0);
    extract_from_finish_list(flash_meta, flash_meta->curr_gc_eb);
    flash_meta->curr_gc_eb->erase_count++;
    flash_meta->curr_gc_eb->curr_write_pos = 0;
    flash_meta->curr_gc_eb->next = NULL;
    flash_meta->curr_gc_eb->prev = NULL;
    insert_to_freelist_head(flash_meta, flash_meta->curr_gc_eb);
    flash_meta->free_num_eb++;
    flash_meta->curr_gc_eb = NULL;
    flash_meta->stats->total_erase_count++;
  }
  free(req);
}

void do_write_to_eb(dev_meta_t *flash_meta, uint64_t lba, int is_gc_write)
{
  uint64_t bucket_num, global_addr;
  int found = 0;

  //check open eb
  if (flash_meta->curr_eb == NULL)
  {
    flash_meta->curr_eb = extract_from_freelist_tail(flash_meta);
    flash_meta->free_num_eb--;
  }

  if(flash_meta->curr_eb == NULL)
  {
    printf("no more free eb, out of space\n");
    exit(1);
  }

  //update forward map
  bucket_num = lba % BUCKET_SIZE;
  global_addr = flash_meta->curr_eb->eb_id * EB_SIZE_IN_SECTOR + flash_meta->curr_eb->curr_write_pos;

  if (flash_meta->index[bucket_num] == 0)
  {
    forward_map_t *entry = malloc(sizeof(forward_map_t));
    entry->lba = lba;
    entry->addr = global_addr;
    entry->next = NULL;
    flash_meta->index[bucket_num] = entry;
  }
  else
  {
    forward_map_t *tmp = flash_meta->index[bucket_num];
    while(tmp)
    {
      if (tmp->lba == lba)
      {
	flash_meta->rev_map[tmp->addr] = -1;  // invalidate old addr
	int old_eb_num = tmp->addr / EB_SIZE_IN_SECTOR;
	flash_meta->logical_eb_list[old_eb_num]->valid_num_sectors--;

	tmp->addr = global_addr;
	found = 1;
	break;
      }
      tmp = tmp->next;
    }
    if (found == 0)
    {
      forward_map_t *entry = malloc(sizeof(forward_map_t));
      entry->lba = lba;
      entry->addr = global_addr;
      entry->next = flash_meta->index[bucket_num];
      flash_meta->index[bucket_num] = entry;
    }
  }

  //update rev_map
  flash_meta->rev_map[global_addr] = lba;

  //increse curr_eb_pos, update eb_valid_sec
  flash_meta->curr_eb->valid_num_sectors++;
  flash_meta->curr_eb->curr_write_pos++;

  //check needs for finalize eb
  if (flash_meta->curr_eb->curr_write_pos == EB_SIZE_IN_SECTOR)
  {
    // EB is full, put to finish_list for gc
    insert_to_finishlist_head(flash_meta, flash_meta->curr_eb);
    flash_meta->curr_eb = extract_from_freelist_tail(flash_meta);
    flash_meta->free_num_eb--;
  }
}

int do_write_to_eb_ms(dev_meta_t *flash_meta, request_t *req, int is_gc_write, int prev_stream_id)
{
  int stream_id = 0, temp;
  uint64_t bucket_num, global_addr;
  int found = 0;
  uint64_t lba = req->lba;

  if (is_gc_write == 1)
    stream_id = 0;
  else
  {
    temp = flash_meta->getid_fnc(flash_meta, req);
    if (temp != 0)
    {
      stream_id = temp;
      prev_stream_id = stream_id;
      //printf("%d ", prev_stream_id);
    }
    else
    {
      //printf("%d ", prev_stream_id);
      stream_id = prev_stream_id;
    }
    //printf("%d ", stream_id);
    //if (stream_id == 0)
    //{
      //printf("prev_stream_id = %d\n", prev_stream_id);
     // stream_id = prev_stream_id;
    //}

  }


  flash_meta->stats->multi_stream_io[stream_id]++;

  if(flash_meta->ms_meta->curr_open_eb[stream_id] == 0 || 
     flash_meta->ms_meta->curr_open_eb[stream_id] == NULL)
  {
    // open the stream
    flash_meta->ms_meta->curr_open_s_num++;
    flash_meta->ms_meta->curr_open_eb[stream_id] = extract_from_freelist_tail(flash_meta);
    flash_meta->free_num_eb--;
  }

  bucket_num = lba % BUCKET_SIZE;
  global_addr = flash_meta->ms_meta->curr_open_eb[stream_id]->eb_id * EB_SIZE_IN_SECTOR + flash_meta->ms_meta->curr_open_eb[stream_id]->curr_write_pos;


  if (flash_meta->index[bucket_num] == 0)
  {
    forward_map_t *entry = malloc(sizeof(forward_map_t));
    entry->lba = lba;
    entry->addr = global_addr;
    entry->next = NULL;
    flash_meta->index[bucket_num] = entry;
  }
  else
  {
    forward_map_t *tmp = flash_meta->index[bucket_num];
    while(tmp != NULL)
    {
      if(tmp->lba == lba)
      {
	flash_meta->rev_map[tmp->addr] = -1;
	int old_eb_num = tmp->addr / EB_SIZE_IN_SECTOR;
	flash_meta->logical_eb_list[old_eb_num]->valid_num_sectors--;

	tmp->addr = global_addr;
	found = 1;
	break;
      }
      tmp = tmp->next;
    }
    if(found == 0)
    {
      forward_map_t *entry = malloc(sizeof(forward_map_t));
      entry->lba = lba;
      entry->addr = global_addr;
      entry->next = flash_meta->index[bucket_num];
      flash_meta->index[bucket_num] = entry;
    }
  }

  flash_meta->rev_map[global_addr] = lba;

  flash_meta->ms_meta->curr_open_eb[stream_id]->valid_num_sectors++;
  flash_meta->ms_meta->curr_open_eb[stream_id]->curr_write_pos++;

  // check needs for finalize eb
  if(flash_meta->ms_meta->curr_open_eb[stream_id]->curr_write_pos == EB_SIZE_IN_SECTOR)
  {
    // EB is full, put to finish_list for gc
    insert_to_finishlist_head(flash_meta, flash_meta->ms_meta->curr_open_eb[stream_id]);
    flash_meta->ms_meta->curr_open_eb[stream_id] = extract_from_freelist_tail(flash_meta);
    flash_meta->free_num_eb--;
  }
  //printf("%d ", stream_id);
  return prev_stream_id;
}

int write_to_eb(dev_meta_t *flash_meta, request_t *req, int is_gc_write, int prev_stream_id)
{
  int stream_id;

  if(flash_meta->total_multi_stream == 0)
    do_write_to_eb(flash_meta, req->lba, is_gc_write);
  else
  {
    prev_stream_id = do_write_to_eb_ms(flash_meta, req, is_gc_write, prev_stream_id);
    //printf("%d ", stream_id);
  }
  

  //check needs for gc
  if(flash_meta->free_num_eb * 100 / flash_meta->gc_threshold <= flash_meta->total_logical_eb && is_gc_write == 0)
  {
    //    printf("not enough eb free --- %d\n", flash_meta->free_num_eb);
    gc_run(flash_meta, prev_stream_id);
  }
  //printf("%d ", stream_id);
return prev_stream_id;
}

void trace_run(dev_meta_t *flash_meta, uint64_t start_lba, uint64_t req_size_bytes, uint64_t timestamp, int prev_stream_id)
{
  int i, temp;
  int stream_id;
  //  int req_size_sector = req_size_bytes / 512;
  int req_size_sector = req_size_bytes;
  request_t *req = malloc(sizeof(request_t));

    //printf("%ld %ld %ld\n", start_lba, req_size_bytes, timestamp);

  flash_meta->stats->req_write_sectors += req_size_sector;
  
  for(i = 0; i < req_size_sector; i++)
  {

    req->lba = start_lba + i;
    req->timestamp = timestamp;
    prev_stream_id = write_to_eb(flash_meta, req, 0, prev_stream_id);
    //printf("%d ", stream_id);
  }
  free(req);
}

int main (int argc, char * argv[])
{
  int c, line_num = 0, prev_stream_id=1;
  int i, loop = 1;
  FILE *fp, *ifp;
  char *ifile, *idict;
  char line[128];
  extern char *optarg;
  extern int optind, optopt, opterr;

  int flash_size = TOTAL_FLASH_SIZE_SECTOR;
  int multi_stream_on = 0;
  int clustering_alg = 0;
  int add_read = 0;
  dev_meta_t *flash_meta;

  uint64_t timestamp = 0;
  uint64_t time_begin = 0;
  char nodes[10];
  char disknum[10];
  char req_type[10];
  uint64_t start_lba;
  uint64_t dict_lba;
  uint64_t dict_stream;
  uint64_t req_size_bytes;
  char resp_time[20];

  while ((c = getopt(argc, argv, "m:c:s:f:d:l:h:r")) != -1) {
    switch(c) {
    case 'f':
      ifile = optarg;
      printf("filename is %s\n", ifile);
      break;
    case 'd':
      idict = optarg;
      printf("dictionary is %s\n", idict);
      break;
    case 's':
      flash_size = atoi(optarg);
      break;
    case 'm':
      multi_stream_on = atoi(optarg);
      break;
    case 'l':
      loop = atoi(optarg);
      break;
    case 'c':
      clustering_alg = atoi(optarg);
    break;
    case 'r':
      add_read = 1;
      break;
    case 'h':
      usage(argv[0]);
      exit(1);
      break;
    default:
      usage(argv[0]);
      break;
     }
   }

  if (ifile == NULL)
  {
    printf ("Please input block trace file\n");
    exit(1);
  }

  if (idict == NULL)
  {
    printf ("Please input dictioary of block trace file\n");
  }

  fp = fopen(ifile, "r");
  if (fp == NULL)
  {
    printf("Failed to open trace file %s\n", ifile);
    exit(1);
  }

  ifp = fopen(idict, "r");
  if (ifp == NULL)
  {
    printf("Failed to open dictionary of trace file %s\n", idict);
  }

  flash_meta = malloc(sizeof(dev_meta_t));
  memset(flash_meta, 0, sizeof(dev_meta_t));
  flash_init(flash_meta, flash_size, multi_stream_on, clustering_alg);

  //printf("total eb %d, total free_eb %d, gc %d, stream %d, curr_open %d\n", flash_meta->total_logical_eb, flash_meta->free_num_eb, flash_meta->gc_threshold, flash_meta->total_multi_stream, flash_meta->curr_open_stream);

  flash_meta->dict = hash_init();
  lseek(fileno(ifp), 0L, SEEK_SET);
  while(fgets(line,sizeof line,ifp)!= NULL)
    {
      sscanf(line, "%ld,%ld", &dict_lba, &dict_stream);
      ht_set_dict(flash_meta->dict, dict_lba, dict_stream);
      //printf("%d, %d\n",dict_lba, ht_set_dict(flash_meta->dict, dict_lba, dict_stream));
      //printf("%d, %d\n",dict_lba, ht_get_dict(flash_meta->dict, dict_lba));
    }
  //printf("%d, %d\n",dict_lba, ht_set_dict(flash_meta->dict, dict_lba, dict_stream));
  //printf("%d, %d\n",dict_lba, ht_get_dict(flash_meta->dict, dict_lba));


  for (i = 0; i < loop; i++)
  {
    printf("loop %d\n", i);
    lseek(fileno(fp), 0L, SEEK_SET);

    while(fgets(line,sizeof line,fp)!= NULL)
    {
      //printf("%d ", stream_id);
      //if (stream_id !=0)
      //{
          //printf("%d ", stream_id);
      //    prev_stream_id = stream_id;
      //}
      //      sscanf(line, "%ld,%[^,],%[^,],%[^,],%ld,%ld,%s", &timestamp, nodes, disknum, req_type, &start_lba, &req_size_bytes, resp_time);

      sscanf(line, "%[^,],%ld,%ld", req_type, &start_lba, &req_size_bytes);

      //      printf("%ld %ld %ld\n", timestamp, start_lba, req_size_bytes);

      flash_meta->stats->req_total++;

      if (add_read == 1 && i == 0)   // only consider read->write for the first loop
      {
	/*
	if (strcmp(req_type, "Read") == 0) 
	{
	  flash_meta->stats->req_read++;
	  continue;  // skip Read requests
	}
	*/
	trace_run(flash_meta, start_lba, req_size_bytes, 0, prev_stream_id);
	flash_meta->stats->req_write++;
      }
      else
      {
	if (strstr(req_type, "W"))
	{
	  trace_run(flash_meta, start_lba, req_size_bytes, 0, prev_stream_id);
	  flash_meta->stats->req_write++;
	}
	else // skip Read requests
	  flash_meta->stats->req_read++;
      }

      line_num++;
      if(line_num % 10000 == 0)
      {
	printf("%d\r", line_num);
	fflush(stdout);
      }
    } // end of while loop
  }

  print_stats(flash_meta);

  free(flash_meta);  
  fclose(fp);
  return 0;
}
