#ifndef __FAN__
#define __FAN__

#include <threshold.h>

class Fan
{
    private:
    int _pin;
    bool _is_on;
    bool _is_automatic;

    public:
    Threshold threshold;
    Fan(int pin);
    void init();
    void turn_on();
    void turn_off();
    void toggle();
    bool is_on();
    bool is_automatic();
    void set_automatic(bool new_mode);
    bool auto_operate(int reading);
};

#endif // __FAN__