#include "light.h"
#include <Arduino.h>
#include <esp_timer.h>


Light::Light(int pin): _pin(pin) {

}

void Light::init() {
    pinMode(_pin, OUTPUT);
    turn_off();
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

void Light::toggle() {
    if(is_on()) {
        turn_off();
    } else {
        turn_on();
    }
}
