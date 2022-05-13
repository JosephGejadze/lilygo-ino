#include "mhz14a.h"
// #define DEBUG

const uint8_t MHZ14A::read_command[] = 
            {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};

MHZ14A::MHZ14A(SoftwareSerial *serial) : serial(serial)
{
}

void MHZ14A::clearSerialBuffer()
{
    while (serial->available())
    {
        serial->read();
    }
}

void MHZ14A::init(){
    serial->begin(9600);
    clearSerialBuffer();
}

uint8_t getCheckSum(uint8_t *packet)
{
    uint8_t checksum = 0;
    for(uint8_t i = 1; i < 8; i++){
        checksum += (uint8_t)packet[i];
    }
    checksum = 0xff - checksum;
    checksum += 1;
    return checksum;
}

int MHZ14A::getCO2(){
    uint8_t read_buffer[9] = {};
  
    serial->write(read_command, sizeof(read_command));
    serial->setTimeout(300);

    #ifndef DEBUG
    serial->readBytes(read_buffer, sizeof(read_buffer));
    #else
    uint8_t bytes_read = serial->readBytes(read_buffer, sizeof(read_buffer));
    Serial.println();
    for(int i=0; i<9; i++){
        if(read_buffer[i] < 0x10){
            Serial.print("0");
        }
        Serial.print(read_buffer[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
    Serial.print("Bytes read: ");
    Serial.println(bytes_read);
    #endif

    uint8_t result_high = read_buffer[2];
    uint8_t result_low  = read_buffer[3];
    int ppm_uart;
    uint8_t checksum = getCheckSum(read_buffer);

    if(checksum == read_buffer[8]){
        ppm_uart = (result_high * 256) + result_low;
    } else{
        ppm_uart = -1;
    }
    
    return ppm_uart;
}