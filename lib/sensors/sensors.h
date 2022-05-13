#ifndef __SENSORS__
#define __SENSORS__

#define FORMATTED_MESSAGE_MAX_LENGTH 32
class Sensors
{
    private:
    int _soil_moisture;
    int _air_humidity;
    int _co2_content;
    int _temperature;
    char _formatted_message[FORMATTED_MESSAGE_MAX_LENGTH + 1];
    
    public:
    Sensors();
    Sensors(int moisture, int humidity, int co2_content, int temperature);
    int get_soil_moisture();
    int get_air_humidity();
    int get_co2_content();
    int get_temperature();
    void set_soil_moisture(int moisture);
    void set_air_humidity(int humidity);
    void set_co2_content(int co2_content);
    void set_temperature(int temperature);
    char* get_formatted_message();
};

#endif // __SENSORS__