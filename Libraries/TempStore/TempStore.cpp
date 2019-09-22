#include "TempStore.h"
#include <Arduino.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

const char ts_csv_elem_example[] = "9999999999, -99.9F,\n";

/*** Private Functions ***/
void TempStore::_attach_ts_node(temp_store_elem *new_node) {
  temp_store_elem *new_ts;
  if (_ll_head == NULL) {
    _ll_head = new_node;
    new_ts = _ll_head;
    // Serial.println("Inserted at head!");
  } else {
    // Traverse to the end of the list
    temp_store_elem *curr_node = _ll_head;
    while(curr_node->next != NULL) {
      curr_node = curr_node->next;
    }
    curr_node->next = new_node;
    new_ts = curr_node;
    // Serial.println("Inserted at end of list!");
  }
  _num_elements++;
}

unsigned long long TempStore::_get_csv_file_size(void) {
  return sizeof(ts_csv_elem_example) * _num_elements;
}

void TempStore::_print_elem(temp_store_elem *ts) {
  //char *ts_csv = (char*)malloc( sizeof(ts_csv_elem_example) );
  unsigned long time_since_start = ts->time - _ll_head->time;

  // snprintf(ts_csv, sizeof(ts_csv_elem_example), "%010lu, % 02.01fF,\n", time_since_start, ts->temp);
  // Serial.print(ts_csv);

  Serial.print(time_since_start);
  Serial.print(", ");
  Serial.print(ts->temp);
  Serial.println();

  //return ts_csv;
}

void TempStore::_free_ll(void) {
  temp_store_elem *curr_node = _ll_head;
  while(curr_node != NULL) {
    temp_store_elem *next = curr_node->next;
    free(curr_node);
    curr_node = next;
  }
}



/*** Public Functions ***/

TempStore::TempStore(void) {
  _ll_head = NULL;
  _num_elements = 0;
}

TempStore::~TempStore(void) {
  dump_list();
}

bool TempStore::store_temp(float new_temp, unsigned long new_time) {
  // Create the new node
  temp_store_elem *new_ts = (temp_store_elem*)malloc(sizeof(temp_store_elem));
  if (new_ts == NULL) {
    Serial.println("[store_temp] failed to allocate memory for new temp_store_elem struct!\n");
    return false;
  }

  // Fill in data
  new_ts->temp = new_temp;
  new_ts->time = new_time;
  new_ts->next = NULL;

  // Attach the new node
  _attach_ts_node(new_ts);
  
  return true;
}

void TempStore::to_csv(void) {
  // Should we use a big char buffer? 
  // Maybe print out after we recieve a special char?

  // Print the expected file size?

  
  // Print out one time,temperature pair at a time?
  temp_store_elem *curr_node = _ll_head;
  while(curr_node != NULL) {

    _print_elem(curr_node);
    
    curr_node = curr_node->next;
  }
}

void TempStore::dump_list(void) {
  _free_ll();
  _ll_head = NULL;
  _num_elements = 0;
}