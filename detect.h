#ifndef DETECT_H_
#define DETECT_H_

#define DETECTION_DUMMY          0
#define DETECTION_LBA_RANGE      1
#define DETECTION_CB             2
#define DETECTION_CB2            3
#define DETECTION_DICT		 4


#define ADDRESS_RANGE            2000000000 //2000000000
#define CHUNK_SIZE_MB            32

void cb_init(dev_meta_t *flash_meta);

int get_stream_id(dev_meta_t *flash_meta, request_t *req);
int get_stream_id_lba_range(dev_meta_t *flash_meta, request_t *req);
int get_stream_id_cb(dev_meta_t *flash_meta, request_t *req);
int get_stream_id_cb2(dev_meta_t *flash_meta, request_t *req);
int get_stream_id_dict(dev_meta_t *flash_meta, request_t *req);


#endif
