#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED
#include <vector>

void GenerateMap(int map_szel, int map_mag);
void AddNumeric(int _x,int _y,int _szel,int _mag,int _min,int _max);
const int cellaszelesseg=20;
const int szegely=(cellaszelesseg/10);

class Szamos
{
public:
    int x,y,szel,mag,aktualis,minimum,maximum;
    bool plusz_gomb,minusz_gomb;
    Szamos(int _x,int _y,int _szel,int _mag,int _min,int _max);
    void kirajzol();
    void check(genv::event ev);
};

class Negyzet
{
public:
    int x,y,szel,allapot;
    Negyzet(int _x,int _y);
    void kirajzol();
};

extern std::vector<std::vector<Negyzet*> > Palya;
extern std::vector<Szamos> Widgets; //Palyameret allito widgetek
#endif // WIDGETS_HPP_INCLUDED
