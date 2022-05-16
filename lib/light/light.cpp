#include "light.h"
#include <Arduino.h>
#include <esp_timer.h>

Light::Light(int pin): _pin(pin) {

}

void Light::init() {
    pinMode(_pin, OUTPUT);
    turn_off();
}

int Light::get_hours_a_day() {
    return _hours_a_day;
}

void Light::set_hours_a_day(int new_hours_a_day) {
    _hours_a_day = new_hours_a_day;
}

void Light::turn_on() {
    digitalWrite(_pin, HIGH);
    _is_on = true;
    _last_turn_on = esp_timer_get_time();
}

void Light::turn_off() {
    digitalWrite(_pin, LOW);
    _is_on = false;
    _last_turn_off = esp_timer_get_time();
}

bool Light::is_on() {
    return _is_on;
}


bool Light::is_automatic() {
    return _is_automatic;
}

void Light::set_automatic(bool new_mode) {
    _is_automatic = new_mode;
}

void Light::toggle() {
    if(is_on()) {
        turn_off();
    } else {
        turn_on();
    }
}

// TODO: consider edge cases of 0 and 24 hours a day
bool Light::auto_operate() {
    if(is_automatic()) {
        unsigned long long time = esp_timer_get_time();
        if(is_on()) {
            if(time - _last_turn_on > get_hours_a_day() * 60 * 60 * 1000 * 1000) {
                turn_off();
            }
        } else {
            if(time - _last_turn_off > (24 - get_hours_a_day()) * 60 * 60 * 1000 * 1000) {
                turn_on();
            }
        }
    }
    return is_on();
}