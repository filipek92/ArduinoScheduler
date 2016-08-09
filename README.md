# ArduinoScheduler
This library is only an extension to "SuperMain" principle.
It contains a list of registred services and if enough time past, it is called
in order of registration, otherwise is skiped.

## Basic usage
Creating two scheduled services, one as fast as possible, second every 200ms 
```
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
```
See an example

## Instalation posibilities
1. Git
  - Use ```git clone https://github.com/filipek92/ArduinoScheduler.git``` in your arduino library folder
2. Arduino
  - TODO
