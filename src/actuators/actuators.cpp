#include "actuators.h"
#include <pump.h>
#include <fan.h>
#include <light.h>
#include <humi.h>
#include "../config.h"

static Pump pump = Pump(PUMP_PIN);
static Humi humi = Humi(HUMID_POWER, HUMID_EN);
static Fan circ_fan = Fan(CIRC_PIN);
static Fan vent_fan = Fan(VENT_PIN);
static Light light = Light(LIGHT_PIN);

Pump* get_pump() {
    return &pump;
}

Humi* get_humi() {
    return &humi;
}

Fan* get_circ_fan() {
    return &circ_fan;
}

Fan* get_vent_fan() {
    return &vent_fan;
}

Light* get_light() {
    return &light;
}

actuators_t get_actuators() {
    actuators_t actuators;
    actuators.pump = get_pump();
    actuators.humi = get_humi();
    actuators.circ_fan = get_circ_fan();
    actuators.vent_fan = get_vent_fan();
    actuators.light = get_light();
    return actuators;
}
