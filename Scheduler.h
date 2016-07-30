/*
  Scheduler.h - Library for scheduing proceses
  from Serial block
  Created by Filip Richter, 30.07.2016.
  Released into the public domain.
*/
#ifndef SCHEDULER_H
#define SCHEDULER_H

#define SERVICES_COUNT  20
#define PERIOD_MODE     true
#define COUNT_MODE      false
#define AS_FAST_AS_POS  0

#include "Arduino.h"
#include "stdint.h"

class Scheduler
{
  public:
    Scheduler();
    bool addService(void (*callback)());
    bool addService(void (*callback)(), unsigned long period);
    bool addService(void (*callback)(), unsigned long period, bool mode);
    void doWork();
    bool setPeriod(void (*callback)(), unsigned long period);
    bool setPeriod(void (*callback)(), unsigned long period, bool mode);
    bool removeService(void (*callback)());
    
  private:
    void (*service_ptrs[SERVICES_COUNT])();
    unsigned long periods[SERVICES_COUNT];
    unsigned long runtime[SERVICES_COUNT];
    uint8_t services_cnt=0;
};

#endif
