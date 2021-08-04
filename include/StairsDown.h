#ifndef STAIRSDOWN_H
#define STAIRSDOWN_H

#include <Room.h>


class StairsDown : public Room
{
   public:
      StairsDown();
      virtual ~StairsDown();
std::string description() const { return "stairs going down"; }
   protected:

   private:
};

#endif // STAIRSDOWN_H
