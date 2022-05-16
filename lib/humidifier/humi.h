#ifndef __HUMI__
#define __HUMI__

#include <threshold.h>

class Humi
{

    private:
    int _power_pin;
    int _enable_pin;
    bool _is_on;
    bool _is_automatic;

    public:
    Threshold threshold;
    Humi(int power_pin, int enable_pin);
    void init();
    void turn_on();
    void turn_off();
    void toggle();
    bool is_on();
    bool is_automatic();
    void set_automatic(bool new_mode);
    bool auto_operate(int reading);
};

#endif /* __HUMI__ */