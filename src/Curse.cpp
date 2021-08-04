#include "Curse.h"
using std::string;

const string Curse::name[4] = {"","Lethargy","The Leech","Forgetfulness" };

Curse::Curse(int num) : number(num), wardingTeasure(0)
{
    if (num == 1) wardingTeasure = 1;
    if (num == 2) wardingTeasure = 3;
    if (num == 3) wardingTeasure = 5;
}

Curse::~Curse()
{
    //dtor
}
