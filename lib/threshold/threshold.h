#ifndef __THRESHOLD__
#define __THRESHOLD__


class Threshold
{
    private:
    int _threshold_lower;
    int _threshold_upper;

    public:
    Threshold();
    Threshold(int threshold_lower, int threshold_upper);
    int get_lower_threshold();
    int get_upper_threshold();
    void set_lower_threshold(int new_threshold);
    void set_upper_threshold(int new_threshold);
    
};


#endif // __THRESHOLD__