#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "Room.h"

class Entrance : public Room
{
   public:
      Entrance();
      virtual ~Entrance();
          std::string description() const { return "the Entrance"; };


   private:
};

#endif // ENTRANCE_H
