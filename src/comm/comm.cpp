#include "comm.h"
#include <stdlib.h>
#include <string>
#include "../actuators/actuators.h"
#include <pump.h>
#include <fan.h>
#include <light.h>
#include <humi.h>
#include <Arduino.h>

static void execute_set_automatic_mode() {
    actuators_t actuators = get_actuators();
    actuators.pump->set_automatic(true);
}

static void execute_set_manual_mode() {
    actuators_t actuators = get_actuators();
    actuators.pump->set_automatic(false);
}

static void execute_manual_turn_on_light() {
    Light* light = get_light();
    if(!light->is_on()) {
        light->turn_on();
    }
}

static void execute_manual_turn_off_light() {
    Light* light = get_light();
    if(light->is_on()) {
        light->turn_off();
    }
}

static void execute_manual_turn_on_vent() {
    Fan* vent_fan = get_vent_fan();
    if(!vent_fan->is_on()) {
        vent_fan->turn_on();
    }
}

static void execute_manual_turn_off_vent() {
    Fan* vent_fan = get_vent_fan();
    if(vent_fan->is_on()) {
        vent_fan->turn_off();
    }
}

static void execute_manual_turn_on_pump() {
    Pump* pump = get_pump();
    if(!pump->is_automatic()){
        if(!pump->is_on()) {
            pump->turn_on();
        }
    }
}

static void execute_manual_turn_off_pump() {
    Pump* pump = get_pump();
    if(!pump->is_automatic()) {
        if(pump->is_on()) {
            pump->turn_off();
        }
    }
} 

static void execute_manual_turn_on_humi() {
    Humi* humi = get_humi();
    if(!humi->is_on()) {
        humi->turn_on();
    }
}

static void execute_manual_turn_off_humi() {
    Humi* humi = get_humi();
    if(humi->is_on()) {
        humi->turn_off();
    }
}

static void execute_auto_set_soil_moisture_threshold(/*char* order,*/ int payload) {
    Pump* pump = get_pump();

    // std::string order_str(order);
    // std::string payload_str = order_str.substr(order_str.find("_") + 1, order_str.length());
    // int new_threshold = atoi(payload_str.c_str());

    pump->threshold.set_lower_threshold(payload);
}

static void execute_auto_set_air_humidity_threshold(int payload) {
    Humi* humi = get_humi();
    humi->threshold.set_lower_threshold(payload);
}

static void execute_auto_set_co2_lower_threshold(int payload) {
    Fan* vent_fan = get_vent_fan();
    vent_fan->threshold.set_lower_threshold(payload);
}

static void execute_auto_set_co2_upper_threshold(int payload) {
    Fan* vent_fan = get_vent_fan();
    vent_fan->threshold.set_upper_threshold(payload);
}

static void execute_auto_set_light_duration(int payload) {
    Light* light = get_light();
    light->set_hours_a_day(payload);
}


ex_status execute_comm_order(char* order) {
    bool status = EX_SUCCESS;
    int order_code = atoi(order);

    // factor out payload extraction here
    std::string order_str(order);
    std::string payload_str = order_str.substr(order_str.find("_") + 1, order_str.length());
    int payload = atoi(payload_str.c_str());

    switch(order_code) {
        case COMM_SET_AUTOMATIC_MODE: {
            execute_set_automatic_mode();
            break;
        }
        case COMM_SET_MANUAL_MODE: {
            execute_set_manual_mode();
            break;
        }
        case COMM_MANUAL_TURN_ON_LIGHT: {
            execute_manual_turn_on_light();
            break;
        }
        case COMM_MANUAL_TURN_OFF_LIGHT: {
            execute_manual_turn_off_light();
            break;
        }
        case COMM_MANUAL_TURN_ON_VENT: {
            execute_manual_turn_on_vent();
            break;
        }
        case COMM_MANUAL_TURN_OFF_VENT: {
            execute_manual_turn_off_vent();
            break;
        }
        case COMM_MANUAL_TURN_ON_PUMP: {
            execute_manual_turn_on_pump();
            break;
        }
        case COMM_MANUAL_TURN_OFF_PUMP: {
            execute_manual_turn_off_pump();
        }
        case COMM_MANUAL_TURN_ON_HUMI: {
            execute_manual_turn_on_humi();
            break;
        }
        case COMM_MANUAL_TURN_OFF_HUMI: {
            execute_manual_turn_off_humi();
            break;
        }
        case COMM_AUTO_SET_SOIL_MOISTURE_THRESHOLD: {
            execute_auto_set_soil_moisture_threshold(payload);
            break;
        }
        
        default: {
            status = EX_FAILURE;
            break;
        }
    }
    return status;
}