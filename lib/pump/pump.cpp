#include "pump.h"
#include <Arduino.h>
#include <threshold.h>

#define PUMP_LOWER_THRESHOLD        (0)
#define PUMP_UPPER_THRESHOLD        (40)

Pump::Pump(int pin) : _pin(pin), _is_on(false)
{
}

void Pump::init() {
    pinMode(_pin, OUTPUT);
    threshold = Threshold(PUMP_LOWER_THRESHOLD, PUMP_UPPER_THRESHOLD);
    turn_off();
}

void Pump::turn_on() {
    digitalWrite(_pin, HIGH);
    _is_on = true;
}

void Pump::turn_off() {
    digitalWrite(_pin, LOW);
    _is_on = false;
}

bool Pump::is_on() {
    return _is_on;
}

bool Pump::toggle() {
    if(is_on()) {
        turn_off();
    } else {
        turn_on();
    }
    return is_on();
}

bool Pump::is_automatic() {
    return _is_automatic;
}

void Pump::set_automatic(bool new_mode) {
    _is_automatic = new_mode;
}

bool Pump::auto_operate(int reading) {
    if(is_automatic()) {
        if(reading < threshold.get_lower_threshold()) {
            turn_on();
        } else {
            turn_off();
        }
    }
    return is_on();
}