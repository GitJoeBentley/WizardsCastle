#ifndef STAIRSUP_H
#define STAIRSUP_H

#include "Room.h"


class StairsUp : public Room
{
   public:
      StairsUp();
      virtual ~StairsUp();
std::string description() const { return "stairs going up"; }
   protected:

   private:
};

#endif // STAIRSUP_H
