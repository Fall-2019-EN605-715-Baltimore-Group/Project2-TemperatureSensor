#ifndef TEMP_STORE_H_
#define TEMP_STORE_H_

#include <stdlib.h>
#include <stdint.h>

/*
 * Temperature "Storage" and "Transmit" Lib
 */
typedef struct temp_store_elem {
  float temp; // Expects a single decimal place of precision in farenheight  
  unsigned long time;
  temp_store_elem *next;
} _temp_store_elem;

class TempStore {
  public:
    TempStore(void);
    ~TempStore(void);
    bool store_temp (float new_temp, unsigned long new_time);
    void to_csv(void);
    void dump_list(void);
    
  private:
    temp_store_elem *_ll_head;
    unsigned long _num_elements;
    void _attach_ts_node(temp_store_elem *new_node);
    unsigned long long _get_csv_file_size(void);
    void _print_elem(temp_store_elem *ts);
    void _free_ll(void);
};



#endif /* TEMP_STORE_CSV_H_ */