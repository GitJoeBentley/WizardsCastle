#ifndef LOCATION_H
#define LOCATION_H

#include <ostream>

class Location
{
   public:
      Location();
      Location(unsigned short, unsigned short,unsigned short);
      unsigned short level() const { return level_; }
      unsigned short row() const { return row_; }
      unsigned short column() const { return column_; }
      unsigned short& level()  { return level_; }
      unsigned short& row()  { return row_; }
      unsigned short& column()  { return column_; }
      bool operator==(const Location& obj);
      bool operator!=(const Location& obj);
      void incLevel();
      void incRow();
      void incColumn();
      void decLevel();
      void decRow();
      void decColumn();
   private:
      unsigned short level_;
      unsigned short row_;
      unsigned short column_;
};

std::ostream& operator<<(std::ostream& out, const Location& loc);

#endif // LOCATION_H
