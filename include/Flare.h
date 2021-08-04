#ifndef FLARE_H
#define FLARE_H

#include <Room.h>


class Flare : public Room
{
   public:
      Flare();
      virtual ~Flare();
std::string description() const { return "flares"; }
   protected:

   private:
};

#endif // FLARE_H
