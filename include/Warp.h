#ifndef WARP_H
#define WARP_H

#include "Room.h"


class Warp : public Room
{
   public:
      Warp();
      virtual ~Warp();
    std::string description() const { return "a warp"; }

   protected:

   private:
};

#endif // WARP_H
