#include <graphics.hpp>
#include "widgets.hpp"
#include "jatekmester.hpp"

int main()
{
    AddNumeric(220,220,60,30,20,50); //Palyameret allito widgetek
    AddNumeric(310,220,60,30,20,50);
    EventLoop();
    return 0;
}
