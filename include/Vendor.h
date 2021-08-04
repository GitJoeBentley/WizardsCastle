#ifndef VENDOR_H
#define VENDOR_H

#include "Room.h"


class Vendor : public Room
{
   public:
      Vendor();
      virtual ~Vendor();
      std::string description() const { return "vendor"; }
      bool isAngry() const { return angry; }
      void setAnger(bool how) { angry = how; }

   protected:

   private:
      bool angry = false;
};

#endif // VENDOR_H
