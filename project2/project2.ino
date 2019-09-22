#include <Arduino.h>
#include <TempStore.h>

#define VOUT_PIN  0
#define BTN0_PIN  3
#define LED0_PIN  13
#define DLY_MS    (1000 * 10) -1 

volatile bool fISR0 = false;

unsigned long timerFlag = 0, timerRead = 0;

TempStore temp_store;

void isr0() {
   if (!fISR0)
   {
      if (digitalRead(BTN0_PIN) == HIGH)  {fISR0 = true;}
   }
}


void setup() {
  pinMode(VOUT_PIN, INPUT);
  pinMode(BTN0_PIN, INPUT_PULLUP);
  pinMode(LED0_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BTN0_PIN), isr0, RISING);

  Serial.begin(9600);
  delay(50);
  while(!Serial) ;
}

inline float CtoF(float tempC)
{
  return (tempC * 1.8) + 32.0;
}

void loop() {

  if (fISR0)
  {
    digitalWrite(LED0_PIN, HIGH);
    // Dump records
    temp_store.to_csv();
    // temp_store.dump_list();
    delay(500);
    digitalWrite(LED0_PIN, LOW);
    fISR0 = false;
  }

  if (timerRead < millis())
  {
    unsigned int readQ = analogRead(VOUT_PIN);
    readQ += analogRead(VOUT_PIN);
    readQ += analogRead(VOUT_PIN); timerRead = millis();
    readQ += analogRead(VOUT_PIN);
    readQ += analogRead(VOUT_PIN);
    //float Tc = (((readQ / 1024.0)*5.0)  - 0.5) * 100.0;
    float Tc = ((readQ / 1024.0)  - 0.5) * 100.0;
    float Tf = CtoF(Tc);
    
    // Write Record
    temp_store.store_temp(Tf, timerRead); 
    
    timerRead += DLY_MS;
  }

  delay(950);
}
