#include "fan.h"
#include <Arduino.h>
#include <threshold.h>

#define FAN_LOWER_THRESHOLD        (400)
#define FAN_UPPER_THRESHOLD        (600)

Fan::Fan(int pin): _pin(pin), _is_on(false) {

}

void Fan::init() {
    pinMode(_pin, OUTPUT);
    threshold = Threshold(FAN_LOWER_THRESHOLD, FAN_UPPER_THRESHOLD);
    turn_off();
}

void Fan::turn_on() {
    digitalWrite(_pin, HIGH);
    _is_on = true;
}

void Fan::turn_off() {
    digitalWrite(_pin, LOW);
    _is_on = false;
}

void Fan::toggle() {
    if(is_on()) {
        turn_off();
    } else {
        turn_on();
    }
}

bool Fan::is_on() {
    return _is_on;
}


bool Fan::is_automatic() {
    return _is_automatic;
}

void Fan::set_automatic(bool new_mode) {
    _is_automatic = new_mode;
}

bool Fan::auto_operate(int reading) {
    if(is_automatic()){
        if(reading > threshold.get_upper_threshold()) {
            turn_on();
        } else if(reading < threshold.get_lower_threshold()) {
            turn_on();
        } else {
            turn_off();
        }
    }
    return is_on();
}