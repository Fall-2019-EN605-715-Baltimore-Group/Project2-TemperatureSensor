#include <TimeLib.h>
#include <TempStore.h>

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 


void setup() {
  // Serial Port Setup
  Serial.begin(115200);
  delay(50);
  while(!Serial) ;

  setSyncProvider( requestSync);  //set function to call when sync required
  Serial.println("Waiting for sync message");
}

void loop() {
  while (timeStatus() == timeNotSet) {
    if (Serial.available()) {
      processSyncMessage();
    }
  }

  TempStore temp_store;

  Serial.println("Storing Temperatures...");
  temp_store.store_temp(60.5, now());
  temp_store.store_temp(61.2, now());
  temp_store.store_temp(68.0, now());
  temp_store.store_temp(32.4, now());
  temp_store.store_temp(-0.5, now());
  temp_store.store_temp(-15.8,now());

  Serial.println("Calling to csv...");
  temp_store.to_csv();

  Serial.println("Dumping the list...\n");
  temp_store.dump_list();

  Serial.println("Done.");
  delay(5000);
}

void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
     }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}
