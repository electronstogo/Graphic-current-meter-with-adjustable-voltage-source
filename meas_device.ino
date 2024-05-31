#include "gui.h"
#include "measurement.h"
#include "data.h"





void setup(void){Serial.begin(9600);}

void loop() 
{
    GUI gui;
    Measurement measurement;


    while(true)
    {
        if(millis() > (g_system.timestamp_sampling + System::SAMPLING_TIME))
        {
            gui.run();
            measurement.run();
            g_system.timestamp_sampling = millis();
        }

        if(millis() > (g_system.timestamp_gui + System::FPS))
        {
            gui.run();
            measurement.run();
            g_system.timestamp_gui = millis();
        }
        
    }

}




