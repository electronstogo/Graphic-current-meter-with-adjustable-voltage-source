#ifndef DATA_H_
#define DATA_H_

#include <stdint.h>





class System
{
    private:


    public:
      static const uint16_t SAMPLING_TIME = 100;
      static const uint16_t FPS = 200;


      uint32_t timestamp_gui;
      uint32_t timestamp_sampling;
};


extern System g_system;






class MeasValue
{
    private:
    public:
      float current;
      float voltage;
      void set_data(float current, float voltage);



};


class Data
{
    private:
        void shift_values();



    public:
        Data();
        static const uint16_t NUMBER_MEASUREMENTS = 250;
        uint16_t number;
        MeasValue values[NUMBER_MEASUREMENTS + 1];

        MeasValue max;
        MeasValue active;

        void add_value(float current, float voltage);
        void update_max(float current, float voltage);
};



extern Data g_data;



#endif