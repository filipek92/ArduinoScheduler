#include <Scheduler.h>

Scheduler scheduler;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  scheduler.addService(ledService, 200); //Run maxximaly every 200ms
  scheduler.addService(serialService); //Run as fast as possible
}

void loop() {
  scheduler.doWork();
}

void ledService(){
  digitalWrite(13, !digitalRead(13));  
}

void serialService(){
  if(Serial.available()){
    Serial.write(Serial.read());
  }  
}
