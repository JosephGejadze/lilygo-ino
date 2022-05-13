#include "humi.h"
#include <Arduino.h>
#include <threshold.h>

#define HUMI_LOWER_THRESHOLD    (0)
#define HUMI_UPPER_THRESHOLD    (40)

Humi::Humi(int power_pin, int enable_pin): 
_power_pin(power_pin), 
_enable_pin(enable_pin), 
_is_on(false) {

}

void Humi::init() {
    pinMode(_power_pin, OUTPUT);
    pinMode(_enable_pin, OUTPUT);
    digitalWrite(_power_pin, LOW);
    digitalWrite(_enable_pin, LOW);
    threshold = Threshold(HUMI_LOWER_THRESHOLD, HUMI_UPPER_THRESHOLD);
}

void Humi::turn_on() {
  digitalWrite(_power_pin, HIGH);
  delay(100);
  digitalWrite(_enable_pin, LOW);
  delay(100);
  digitalWrite(_enable_pin, HIGH);
  _is_on = true;
}

void Humi::turn_off() {
    digitalWrite(_power_pin, LOW);
    _is_on = false;
}

void Humi::toggle() {
    if(_is_on) {
        turn_off();
    } else {
        turn_on();
    }
}

bool Humi::is_on() {
    return _is_on;
}

bool Humi::operate(int reading) {
    if(reading < threshold.get_upper_threshold()) {
        turn_on();
    } else {
        turn_off();
    }
    return is_on();
}