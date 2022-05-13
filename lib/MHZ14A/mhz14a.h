#ifndef __MHZ14A__
#define __MHZ14A__

#include <SoftwareSerial.h>

class MHZ14A
{
private:
    SoftwareSerial *serial;
    static const uint8_t read_command[];
    void clearSerialBuffer();

public:
    MHZ14A(SoftwareSerial *serial);
    void init();
    int getCO2();
};

#endif // __MHZ14A__