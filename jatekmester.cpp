#include <iostream>
#include <graphics.hpp>
#include "jatekmester.hpp"
#include "widgets.hpp"
#include <vector>

using namespace std;
using namespace genv;

int player=0;
int map_szel=20;
int map_mag=20;
bool win=false;
bool play=false;
bool dontetlen=false;
vector<Negyzet> sorbanX, sorban3szog;

void Check(Negyzet &n, event ev)
{
    if(ev.pos_x<(n.x+cellaszelesseg-(szegely/4)) && ev.pos_x>(n.x+(szegely/4)) && ev.pos_y>(n.y+(szegely/4)) &&ev.pos_y<(n.y+cellaszelesseg-(szegely/4)) &&ev.button==btn_left )
    {
        if(n.allapot==-1)
        {
            if(player==0) {n.allapot=0;player=1;}
            else{n.allapot=1;player=0;}
        }
    }
}

void CheckX(int i, int j, vector<vector<Negyzet> > Palya)
{
    if(Palya[i][j].allapot==0)
    {
        sorbanX.push_back(Palya[i][j]);
        if(sorbanX.size()==5){win=true;play=false;return;}
    }
    else sorbanX.clear();
}

void Check_3szog(int i, int j, vector<vector<Negyzet> > Palya)
{
    if(Palya[i][j].allapot==1)
    {
        sorban3szog.push_back(Palya[i][j]);
        if(sorban3szog.size()==5){win=true;play=false;return;}
    }
    else sorban3szog.clear();
}

void FinalCheck(vector<vector<Negyzet> > Palya)
{
    int palya_mag=Palya.size();
    int palya_szel=Palya[0].size();
    //fuggoleges
    for(int i=0;i<palya_mag;i++)
    {
        for(int j=0;j<palya_szel;j++)
        {
            CheckX(i,j,Palya);
            Check_3szog(i,j,Palya);
        }
        sorbanX.clear();
        sorban3szog.clear();
    }
    //vizszintes
    for(int j=0;j<palya_szel;j++)
    {
        for(int i=0;i<palya_mag;i++)
        {
            CheckX(i,j,Palya);
            Check_3szog(i,j,Palya);
        }
        sorbanX.clear();
        sorban3szog.clear();
    }
    //keresztbe balra le (x=i+j allando)
    for(int x=0;x<(palya_mag+palya_szel-1);x++)
    {
        int i=(x<palya_szel ? 0 : x-palya_szel+1);
        while(i<palya_mag && x-i>=0)
        {
            CheckX(i,x-i,Palya);
            Check_3szog(i,x-i,Palya);
            i++;
        }
        sorbanX.clear();
        sorban3szog.clear();
    }
    //keresztbe jobbra le (x=i-j allando)
    for(int x=palya_mag-1;x>-palya_szel;x--)
    {
        int i=(x>0 ? x : 0);
        while(i<palya_mag && i-x<palya_szel)
        {
            CheckX(i,i-x,Palya);
            Check_3szog(i,i-x,Palya);
            i++;
        }
        sorbanX.clear();
        sorban3szog.clear();
    }
    //betelt-e:
    int ures=0;
    for(int i=0;i<Palya.size();i++)
    {
        for(int j=0;j<Palya[i].size();j++)
        {
            if(Palya[i][j].allapot==-1) ures++;
        }
    }
    if(ures==0) {play=false;win=true;dontetlen=true;}
    gout<<refresh;
}

void Play(event ev)
{
    vector<vector<Negyzet> > dereferalt;
    for(int i=0;i<Palya.size();i++)
    {
        vector<Negyzet> v;
        for(int j=0;j<Palya[i].size();j++)
        {
            Check(*Palya[i][j],ev);
            Palya[i][j]->kirajzol();
            v.push_back(*Palya[i][j]);
        }
        dereferalt.push_back(v);
    }
    FinalCheck(dereferalt);
}

void Menu(event ev)
{
    gout.open(600,500);
    gout<<move_to(0,0)<<color(0,0,0)<<box(600,500);
    gout.load_font("LiberationSans-Regular.ttf",40);
    gout<<move_to(230,20)<<color(146,165,67)<<text("AMOBA");
    gout.load_font("LiberationSans-Regular.ttf",18);
    gout << move_to(15,120)<<text("A jatek egyszeru:");
    gout<<move_to(15,140)<<text("Gyujts ossze 5 ugyanolyan szimbolumot fuggolegesen, vizszintesen");
    gout<<move_to(15,160)<<text("vagy atlosan es gyozd le ellenfeled");
    gout<<move_to(15,180)<<text("A palya meretet itt tudod beallitani:");
    gout<<move_to(290,220)<<text("X");

    for(int i=0;i<Widgets.size();i++)
    {
        Widgets[i].check(ev);
        Widgets[i].kirajzol();

    }
    gout<<move_to(10,260)<<color(146,165,67)<<text("Keszen allsz?");
    gout<<move_to(10,280)<<text("A jatek kezdesehez nyomj Entert!");
    gout<<move_to(10,300)<<text("Kilepeshez pedig hasznald az Esc gombot.");
    gout<<move_to(10,320)<<text("Jo szorakozast!");

    map_szel=Widgets[0].aktualis;
    map_mag=Widgets[1].aktualis;
    if(ev.keycode==key_enter)
    {
        play=true;
        GenerateMap(Widgets[0].aktualis,Widgets[1].aktualis);
    }
    gout<<refresh;
}

void Death(event ev)
{
    gout<<move_to(0,0)<<color(0,0,0)<<box((map_szel*cellaszelesseg+20),(map_mag*cellaszelesseg+20));
    if(dontetlen)
    {
        gout<<move_to(10,40)<<color(249,242,164)<<text("A palya betelt, igy a jatek dontetlen!");
        gout<<move_to(10,70)<<text("Gratulalunk mindket jatekosnak!");
    }
    else
    {
        gout<<move_to(10,50)<<color(249,242,164)<<text("A nyertes: ");
        string melyik_jatekos;
        if(player==1)melyik_jatekos="Az 1. jatekos (X)";
        else melyik_jatekos="A 2. jatekos (haromszog)";
        gout<<move_to(10,70)<<text(melyik_jatekos);
        gout<<move_to(10,90)<<text("Gratulalunk!");
    }
    gout<<move_to(10,200)<<text("Uj jatekhoz kerjuk nyomj Entert!");
    gout<<move_to(10,230)<<text("Fomenuhoz kerjuk nyomj Space-t!");
    gout<<move_to(10,280)<<text("Kilepeshez hasznald az Esc gombot!");

    if(ev.keycode==key_enter){win=false;play=true;GenerateMap(map_szel,map_mag);Play(ev);}
    if(ev.keycode==key_space){win=false;play=false;Menu(ev);}

    gout<<refresh;
}

void EventLoop()
{
    event ev;
    while(gin >> ev)
    {
        if(ev.keycode==key_escape)return;
        if(win==false)
        {
            if(play==false) Menu(ev);
            if(play==true)Play(ev);
        }
        if(win==true)
        {
            Death(ev);
        }
    }
}
