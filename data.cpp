#include "data.h"



Data g_data;
System g_system;



void MeasValue::set_data(float current, float voltage)
{
    this->current = current;
    this->voltage = voltage;
}





Data::Data()
{
    number = 0;
}


void Data::shift_values()
{
    for(uint16_t i = 0; i < NUMBER_MEASUREMENTS; i++)
    {
        values[i].set_data(values[i + 1].current, values[i + 1].voltage);
    }
}




void Data::add_value(float current, float voltage)
{
    if(number >= NUMBER_MEASUREMENTS)
    {
        shift_values();
    }

    values[number].set_data(current, voltage);
    active.set_data(current, voltage);
    number = number >= NUMBER_MEASUREMENTS ? NUMBER_MEASUREMENTS : number + 1;




    update_max(current, voltage);
}



/**
* Update the maximum measured values.
*/
void Data::update_max(float current, float voltage)
{
    max.current = 5;
    max.voltage = 5;

    for(uint16_t i = 0; i < number; i++)
    {
        max.current = (max.current < values[i].current) ? values[i].current : max.current; 
        max.voltage = (max.voltage < values[i].voltage) ? values[i].voltage : max.voltage;
    }
}
