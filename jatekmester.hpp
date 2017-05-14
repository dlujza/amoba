#ifndef JATEKMESTER_H_INCLUDED
#define JATEKMESTER_H_INCLUDED
#include <vector>
#include "widgets.hpp"

extern int player,map_szel,map_mag;
extern bool win,play,dontetlen;
extern std::vector<Negyzet> sorbanX, sorban3szog;
void Check(Negyzet &n, genv::event ev);
void CheckX(int i, int j, std::vector<std::vector<Negyzet> > Palya);
void Check_3szog(int i, int j, std::vector<std::vector<Negyzet> > Palya);
void FinalCheck(std::vector<std::vector<Negyzet> > Palya);
void Play(genv::event ev);
void Menu(genv::event ev);
void Death(genv::event ev);
void EventLoop();

#endif // JATEKMESTER_H_INCLUDED
