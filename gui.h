#ifndef GUI_H_
#define GUI_H_



#include <stdint.h>





class GUI
{
    private:
        void flush();

        static const uint16_t WIDTH = 320;
        static const uint16_t HEIGHT = 240;

        const uint16_t X[2] = {45, 315};
        const uint16_t Y[2] = {220, 50};
        const uint16_t GRAPH_HEIGHT = Y[0] - Y[1];
        const uint16_t GRAPH_WIDTH = X[1] - X[0];


    public:
        GUI();
        void run();
        void draw_graph_frame();
        void draw_graph_curves();
        void draw_current(float max);
        void draw_voltage(float max);
        void draw_text_infos();
};





#endif