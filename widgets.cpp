#include <graphics.hpp>
#include "widgets.hpp"
#include "jatekmester.hpp"
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;
using namespace genv;

vector<vector<Negyzet*> > Palya;
vector<Szamos> Widgets;

void GenerateMap(int map_szel, int map_mag)
{
    Palya.clear();
    gout.open((map_szel*cellaszelesseg+20),(map_mag*cellaszelesseg+20));
    for(int i=0; i<map_szel; i++)
    {
        vector<Negyzet* > w;
        for(int j=0; j<map_mag;j++)
        {
            Negyzet* n=new Negyzet(i*cellaszelesseg+10,j*cellaszelesseg+10);
            w.push_back(n);
        }
        Palya.push_back(w);
    }
}

void AddNumeric(int _x,int _y,int _szel,int _mag,int _min,int _max)
{
    Szamos w(_x,_y,_szel,_mag,_min,_max);
    Widgets.push_back(w);
}

Szamos::Szamos(int _x,int _y,int _szel,int _mag,int _min,int _max)
    {
        x=_x;
        y=_y;
        szel=_szel;
        mag=_mag;
        plusz_gomb=false;
        minusz_gomb=false;
        aktualis=_min;
        minimum=_min;
        maximum=_max;
    }

Negyzet::Negyzet(int _x,int _y)
    {
        x=_x;
        y=_y;
        szel=cellaszelesseg;
        allapot=-1;
    }

void Szamos::kirajzol()
{
    if(plusz_gomb) gout<<move_to(szel+x-mag/2,y)<<color(223,231,194)<<box(mag/2,mag/2);
    if(minusz_gomb) gout<<move_to(szel+x-mag/2,y+mag/2)<<color(223,231,194)<<box(mag/2,mag/2);

    gout<<color(146,165,67)<<move_to(x,y)<<box(szel,2)<<box(-2,mag)<<box(-szel,-2)<<box(2,-mag);
    gout<<move_to(szel+x-mag/2,y)<<box(2,mag)<<move_to(szel+x-mag/2,y+mag/2)<<box(mag/2,2);
    gout<<move_to(szel+x-mag/2.5,y-mag/10)<<text("+")<<move_to(szel+x-mag/2.5,y+mag/10)<<text("_");
    stringstream ss;
    string aktualis_szam;
    ss<<aktualis;
    ss>>aktualis_szam;
    gout<<move_to(x+10,y+mag/10)<<text(aktualis_szam);
}

void Szamos::check(event ev)
{
    if(ev.pos_x>(szel+x-mag/2) && ev.pos_x<(szel+x) && ev.pos_y>y && ev.pos_y<y+mag/2)
    {
        plusz_gomb=true;
        if(ev.button==btn_left)aktualis++;
    }
    else plusz_gomb=false;
    if(ev.pos_x>(szel+x-mag/2) && ev.pos_x<(szel+x) && ev.pos_y>y+mag/2 && ev.pos_y<y+mag)
    {
        minusz_gomb=true;
        if(ev.button==btn_left)aktualis--;
    }
    else minusz_gomb=false;

    if(aktualis<minimum) aktualis=minimum;
    if(aktualis>maximum) aktualis=maximum;
}

void Negyzet::kirajzol()
{
    gout<<move_to(x,y)<<color(92,71,107)<<box(szel,szel)<<move_to(x+(szegely/2),y+(szegely/2))<<color(0,0,0)<<box(szel-szegely,szel-szegely);
    if(allapot==0)
    {
        gout<<color(225,196,215)<<move_to(x+5,y+5)<<line_to((x+cellaszelesseg-5),(y+cellaszelesseg-5));
        gout<<move_to(x+cellaszelesseg-5,y+5)<<line_to(x+5,y+cellaszelesseg-5);
    }
    if(allapot==1)
    {
        gout<<color(200,191,231)<<move_to(x+5,y+cellaszelesseg-5)<<line_to(x+cellaszelesseg-5,y+cellaszelesseg-5)<<line_to(x+cellaszelesseg/2,y+5)<<line_to(x+5,y+cellaszelesseg-5);
    }
}

