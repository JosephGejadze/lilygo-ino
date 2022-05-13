#ifndef __ACTUATORS__
#define __ACTUATORS__

#include <pump.h>
#include <fan.h>
#include <light.h>
#include <humi.h>

typedef struct {
    Pump* pump;
    Fan* circ_fan;
    Fan* vent_fan;
    Humi* humi;
    Light* light;
} actuators_t;

Pump* get_pump();
Humi* get_humi();
Fan* get_circ_fan();
Fan* get_vent_fan();
Light* get_light();
actuators_t get_actuators();

#endif // __ACTUATORS__