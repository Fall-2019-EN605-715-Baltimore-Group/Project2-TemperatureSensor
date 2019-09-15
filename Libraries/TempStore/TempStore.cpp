#include "TempStore.h"

#include <TimeLib.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <Arduino.h>

const char ts_csv_elem_example[] = "24:59:59, -15.5F,\n";

/*** Private Functions ***/
void TempStore::_attach_ts_node(temp_store_elem *new_node) {
  if (_num_elements == 0) {
    _ll_head = new_node;
  } else {
    // Traverse to the end of the list
    temp_store_elem *curr_node = _ll_head;
    while(curr_node->next != NULL) {
      curr_node = curr_node->next;
    }
    curr_node->next = new_node;
    _num_elements++;
  }
}

unsigned long long TempStore::_get_csv_file_size(void) {
  return sizeof(ts_csv_elem_example) * _num_elements;
}

char* TempStore::_ts_elem_to_str(temp_store_elem *ts) {
  int hours = numberOfHours(ts->time);
  int minutes = numberOfMinutes(ts->time);
  int seconds = numberOfSeconds(ts->time);
  char *ts_csv = (char *)malloc( sizeof(ts_csv_elem_example) );
  snprintf(ts_csv, sizeof(ts_csv_elem_example), "%02d:%02d:%02d, % 02.1fF,\n",
  hours, minutes, seconds, ts->temp);
  return ts_csv;
}

void TempStore::_free_ll(void) {
  temp_store_elem *curr_node = _ll_head;
  while(curr_node->next != NULL) {
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
  _free_ll();
}

bool TempStore::store_temp(float new_temp, long new_time) {
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
  while(curr_node->next != NULL) {

    char *ts_ll_str_elem = _ts_elem_to_str(curr_node);
    Serial.print( ts_ll_str_elem );
    free(ts_ll_str_elem);

    curr_node = curr_node->next;
  }
}

void TempStore::dump_list(void) {
  _free_ll();
}