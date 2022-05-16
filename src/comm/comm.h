#ifndef __COMM__
#define __COMM__

#define EX_SUCCESS      (true)
#define EX_FAILURE      (false)

typedef bool ex_status;

enum COMM { 
    COMM_SET_MANUAL_MODE                     = 5,
    COMM_SET_AUTOMATIC_MODE                  = 6,
    COMM_SYNC_THRESHOLDS                     = 7,
    COMM_MANUAL_TURN_ON_LIGHT                = 10,
    COMM_MANUAL_TURN_OFF_LIGHT               = 11,
    COMM_MANUAL_TURN_ON_VENT                 = 12,
    COMM_MANUAL_TURN_OFF_VENT                = 13,
    COMM_MANUAL_TURN_ON_PUMP                 = 14,
    COMM_MANUAL_TURN_OFF_PUMP                = 15,
    COMM_MANUAL_TURN_ON_HUMI                 = 16,
    COMM_MANUAL_TURN_OFF_HUMI                = 17,
    COMM_AUTO_SET_SOIL_MOISTURE_THRESHOLD    = 20,
    COMM_AUTO_SET_AIR_HUMIDITY_THRESHOLD     = 21,
    COMM_AUTO_SET_CO2_LOWER_THRESHOLD        = 22,
    COMM_AUTO_SET_CO2_UPPER_THRESHOLD        = 23,
    COMM_AUTO_SET_LIGHT_DURATION             = 24,
};

ex_status execute_comm_order(int order_code, int order_payload);

#endif // __COMM__