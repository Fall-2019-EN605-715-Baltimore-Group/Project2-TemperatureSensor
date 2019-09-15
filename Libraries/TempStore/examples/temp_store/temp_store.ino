#include <TempStore.h>


void setup() {
  // Serial Port Setup
  Serial.begin(115200);
  delay(50);
  while(!Serial) ;

  Serial.println("Setup Complete!");
}

void loop() {

  TempStore temp_store;

  Serial.println("Storing Temperatures...");
  temp_store.store_temp(605, millis()); delay(10);
  temp_store.store_temp(612, millis()); delay(10);
  temp_store.store_temp(680, millis()); delay(10);
  temp_store.store_temp(324, millis()); delay(10);
  temp_store.store_temp(-5, millis()); delay(10);
  temp_store.store_temp(-158, millis()); delay(10);

  Serial.println("Calling to csv...");
  temp_store.to_csv();

  Serial.println("Dumping the list...\n");
  temp_store.dump_list();

  Serial.println("Done.");
  delay(5000);
}

