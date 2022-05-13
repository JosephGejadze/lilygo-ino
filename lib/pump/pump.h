#ifndef __PUMP__
#define __PUMP__

#include <threshold.h>

class Pump
{
    private:
    int _pin;
    bool _is_on;
    bool _is_automatic;

    public:
    Threshold threshold;
    Pump(int pin);
    void init();
    void turn_on();
    void turn_off();
    bool is_on();
    bool toggle();
    bool is_automatic();
    void set_automatic(bool new_mode);
    bool auto_operate(int reading);
};
#endif // __PUMP__