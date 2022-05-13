#include "sensors.h"

#include <stdio.h>

Sensors::Sensors(){
    _air_humidity = 0;
    _soil_moisture = 0;
    _temperature = 0;
    _co2_content = 0;
}

Sensors::Sensors(int moisture, int humidity, int co2_content, int temperature){
    _air_humidity = humidity;
    _soil_moisture = moisture;
    _temperature = temperature;
    _co2_content = co2_content;
}

int Sensors::get_air_humidity(){
    return _air_humidity;
}

void Sensors::set_air_humidity(int humidity){
    _air_humidity = humidity;
}

int Sensors::get_soil_moisture(){
    return _soil_moisture;
}

void Sensors::set_soil_moisture(int moisture){
    _soil_moisture = moisture;
}

int Sensors::get_co2_content(){
    return _co2_content;
}

void Sensors::set_co2_content(int co2_content){
    _co2_content = co2_content;
}

int Sensors::get_temperature(){
    return _temperature;
}

void Sensors::set_temperature(int temperature){
    _temperature = temperature;
}

char* Sensors::get_formatted_message() {
    sprintf(_formatted_message, "%d,%d,%d,%d", 
            get_air_humidity(),
            get_soil_moisture(),
            get_co2_content(),
            get_temperature()
    );
    return _formatted_message;
}