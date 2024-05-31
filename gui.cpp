#include "gui.h"
#include "data.h"
#include "SPI.h"
#include "TFT_eSPI.h"


TFT_eSPI display = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&display);









GUI::GUI()
{
      display.begin();
      display.setRotation(1);
      display.fillScreen(TFT_BLACK);
}





void GUI::run()
{
    sprite.createSprite(320, 240);
    sprite.fillSprite(TFT_BLACK);

    draw_graph_frame();
    draw_graph_curves();

    draw_text_infos();

    flush();
}






void GUI::flush()
{
    sprite.pushSprite(0, 0);
}



void GUI::draw_graph_frame()
{
    sprite.drawLine(X[0], Y[0], X[0], Y[1], TFT_WHITE);
    sprite.drawLine(X[0], Y[0], X[1], Y[0], TFT_WHITE);


    // Y axis.
    sprite.drawLine(X[0] - 4, Y[1], X[0] + 4, Y[1], TFT_WHITE);
    sprite.drawLine(X[0] - 4, Y[1] + GRAPH_HEIGHT / 5, X[0] + 4, Y[1] + GRAPH_HEIGHT / 5, TFT_WHITE);
    sprite.drawLine(X[0] - 4, Y[1] + (GRAPH_HEIGHT / 5) * 2, X[0] + 4, Y[1] + (GRAPH_HEIGHT / 5) * 2, TFT_WHITE);
    sprite.drawLine(X[0] - 4, Y[1] + (GRAPH_HEIGHT / 5) * 3, X[0] + 4, Y[1] + (GRAPH_HEIGHT / 5) * 3, TFT_WHITE);
    sprite.drawLine(X[0] - 4, Y[1] + (GRAPH_HEIGHT / 5) * 4, X[0] + 4, Y[1] + (GRAPH_HEIGHT / 5) * 4, TFT_WHITE);

    // X axis.
    sprite.drawLine(X[0] + (GRAPH_WIDTH / 5), Y[0] - 4, X[0] + (GRAPH_WIDTH / 5), Y[0] + 4, TFT_WHITE);
    sprite.drawLine(X[0] + (GRAPH_WIDTH / 5) * 2, Y[0] - 4, X[0] + (GRAPH_WIDTH / 5) * 2, Y[0] + 4, TFT_WHITE);
    sprite.drawLine(X[0] + (GRAPH_WIDTH / 5) * 3, Y[0] - 4, X[0] + (GRAPH_WIDTH / 5) * 3, Y[0] + 4, TFT_WHITE);
    sprite.drawLine(X[0] + (GRAPH_WIDTH / 5) * 4, Y[0] - 4, X[0] + (GRAPH_WIDTH / 5) * 4, Y[0] + 4, TFT_WHITE);
    sprite.drawLine(X[0] + (GRAPH_WIDTH / 5) * 5, Y[0] - 4, X[0] + (GRAPH_WIDTH / 5) * 5, Y[0] + 4, TFT_WHITE);

}



void GUI::draw_graph_curves()
{
    draw_current(g_data.max.current);
    draw_voltage(g_data.max.voltage);
}



void GUI::draw_current(float max)
{
    uint16_t y = Y[0] - (g_data.values[0].current / max) * (float)GRAPH_HEIGHT;
    uint16_t y_old = y;


    for(uint16_t i = 1; i < g_data.number; i++)
    {
        y = Y[0] - (g_data.values[i].current / max) * (float)GRAPH_HEIGHT;
        sprite.drawLine(X[0] + i, y_old, X[0] + i + 1, y, TFT_RED);
        y_old = y;
    }
}



void GUI::draw_voltage(float max)
{
    uint16_t y = Y[0] - (g_data.values[0].voltage / max) * (float)GRAPH_HEIGHT;
    uint16_t y_old = y;


    for(uint16_t i = 1; i < g_data.number; i++)
    {
        y = Y[0] - (g_data.values[i].voltage / max) * (float)GRAPH_HEIGHT;
        sprite.drawLine(X[0] + i, y_old, X[0] + i + 1, y, TFT_YELLOW);
        y_old = y;
    }
}




void GUI::draw_text_infos()
{
    sprite.setTextColor(TFT_RED);
    String string;

    if(g_data.active.current >= 1000)
    {
        string = String(g_data.active.current / 1000.0, 1) + " A";    
    }
    else
    {
        string = String(g_data.active.current, 1) + " mA";
    }
    
    sprite.drawRightString(string, 200, 2, 4);


    // Y axis current.
    for(uint16_t i = 0; i < 5; i++)
    {
        if(g_data.max.current >= 1000)
        {
            string = String(int16_t(g_data.max.current / 5000) * (i + 1));  
        }
        else
        {
            string = String(int16_t(g_data.max.current / 5) * (i + 1));
        }
        
        sprite.drawRightString(string, X[0] - 5, Y[0] - (GRAPH_HEIGHT / 5) * (i + 1) - 15, 2);
    }


    sprite.setTextColor(TFT_YELLOW);
    string = String(g_data.active.voltage, 1) + " V";
    sprite.drawRightString(string, 80, 2, 4);



    // Y axis voltage.
    for(uint16_t i = 0; i < 5; i++)
    {
        string = String((g_data.max.voltage / 5) * (i + 1), 1);
        sprite.drawRightString(string, X[0] - 5, Y[0] - (GRAPH_HEIGHT / 5) * (i + 1), 2);
    }

    sprite.setTextColor(TFT_WHITE);
    
    // X axis samples.
    for(uint16_t i = 0; i < 5; i++)
    {
        string = String((GRAPH_WIDTH / 5) * (i + 1));
        sprite.drawRightString(string, X[0] + (GRAPH_WIDTH / 5) * (i + 1) + 6, HEIGHT - 15, 2);
    }


    sprite.drawRightString("SAMPLE TIME", WIDTH - 2, 2, 2);
    string = String(System::SAMPLING_TIME) + " ms";
    sprite.drawRightString(string, WIDTH - 2, 20, 2);

}