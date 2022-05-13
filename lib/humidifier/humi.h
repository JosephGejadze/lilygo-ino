#ifndef __HUMI__
#define __HUMI__

#include <threshold.h>

class Humi
{

    private:
    int _power_pin;
    int _enable_pin;
    bool _is_on;

    public:
    Threshold threshold;
    Humi(int power_pin, int enable_pin);
    void init();
    void turn_on();
    void turn_off();
    void toggle();
    bool is_on();
    bool operate(int reading);
};

#endif /* __HUMI__ */