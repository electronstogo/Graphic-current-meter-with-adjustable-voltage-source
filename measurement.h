#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_


#include <stdint.h>





/*class INA219
{
    private:
        static const uint8_t ADDRESS = 0x40;


        struct Registers
        {
            static const uint8_t CONFIG = 0x0;
            static const uint8_t SHUNT_VOLTAGE = 0x01;
            static const uint8_t BUS_VOLTAGE = 0x02;
            static const uint8_t POWER = 0x03;
            static const uint8_t CURRENT = 0x04;
            static const uint8_t CALIBRATION = 0x05;
        
        };




    public:
        INA219();
        float read_shunt_voltage();
        uint16_t read_power();
        float read_current();
        
};*/ 



class Measurement
{
    private:
        //INA219 ina219;



    public:
        Measurement();
        void run();


};



#endif