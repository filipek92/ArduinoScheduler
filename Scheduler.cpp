/*
  Scheduler.cpp - Library for parsing commands
  from Serial block
  Created by Filip Richter, 30.07.2016.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Scheduler.h"

Scheduler::Scheduler()
{
  for (uint8_t i = 0; i < SERVICES_COUNT; i++) {
    if (service_ptrs[i] != 0) continue; //Position already registered
    service_ptrs[services_cnt] = 0;
  }
}

bool Scheduler::addService(void (*callback)())
{
  return addService(callback, AS_FAST_AS_POS, PERIOD_MODE);
}

bool Scheduler::addService(void (*callback)(), unsigned long period)
{
  return addService(callback, period, PERIOD_MODE);
}
bool Scheduler::addService(void (*callback)(), unsigned long period, bool mode) {
  for (uint8_t i = 0; i < SERVICES_COUNT; i++) {
    if (service_ptrs[i] != 0) continue; // Position already registered
    service_ptrs[i] = callback;
    periods[i] = period;
    //mode
    if (i >= services_cnt) services_cnt = i + 1;
    return true;
  }
  return false;
}

bool Scheduler::removeService(void (*callback)()) {
  for (uint8_t i = 0; i < SERVICES_COUNT; i++) {
    if (service_ptrs[i] != callback) continue; // Callback not same
    service_ptrs[i] = 0;
    return true;
  }
  return false;
}

bool Scheduler::setPeriod(void (*callback)(), unsigned long period) {
  setPeriod(callback, period);
}

bool Scheduler::setPeriod(void (*callback)(), unsigned long period, bool mode) {
  for (uint8_t i = 0; i < services_cnt; i++) {
    if (service_ptrs[i] != callback) continue; // Callback not same
    periods[i] = period;
    //mode
    return true;
  }
  return false;
}

void Scheduler::doWork()
{
  for (uint8_t i = 0; i < services_cnt; i++) {
    if (periods[i] && ((millis() - runtime[i]) < periods[i])) {
      continue;
    }
    if (service_ptrs[i] == 0) continue;

    runtime[i] = millis();
    service_ptrs[i](); //Call service
  }
}
