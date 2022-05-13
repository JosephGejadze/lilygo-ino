#include "threshold.h"

Threshold::Threshold():
_threshold_lower(0),
_threshold_upper(100) {

}

Threshold::Threshold(int threshold_lower, int threshold_upper):
_threshold_lower(threshold_lower),
_threshold_upper(threshold_upper) {
    
}

int Threshold::get_lower_threshold() {
    return _threshold_lower;
}

int Threshold::get_upper_threshold() {
    return _threshold_upper;
}

void Threshold::set_lower_threshold(int new_threshold) {
    _threshold_lower = new_threshold;
}

void Threshold::set_upper_threshold(int new_threshold) {
    _threshold_upper = new_threshold;
}