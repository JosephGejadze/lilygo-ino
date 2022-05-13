#ifndef __LIGHT__
#define __LIGHT__

class Light
{
    private:
    int _pin;
    bool _is_on;
    int _hours_a_day;
    unsigned long long _last_turn_on;
    unsigned long long _last_turn_off;

    public:
    Light(int pin);
    void init();
    void turn_on();
    void turn_off();
    void toggle();
    bool is_on();
    int get_hours_a_day();
    void set_hours_a_day(int new_hours_a_day);
    bool operate();


};

#endif // __LIGHT__