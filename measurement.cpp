#include "measurement.h"
#include "data.h"
#include <Wire.h>
#include "Adafruit_INA219.h"



Adafruit_INA219 ina219;



Measurement::Measurement()
{
    ina219.begin();
}




void Measurement::run()
{
    float voltage = ina219.getBusVoltage_V();
    float current = ina219.getCurrent_mA();

    // Filter.
    voltage = voltage < 0.1 ? 0 : voltage;
    current = current < 0.1 ? 0 : current;

    g_data.add_value(current, voltage);
}
