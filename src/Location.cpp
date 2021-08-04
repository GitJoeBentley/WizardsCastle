#include "Location.h"

Location::Location() : level_(0), row_(0), column_(3)
{
}

Location::Location(unsigned short l, unsigned short r,unsigned short c)
    : level_(l), row_(r), column_(c) {}


std::ostream& operator<<(std::ostream& out, const Location& loc)
{

    out << "( " << loc.row() + 1 << " , " << loc.column() + 1 << " ) Level " << loc.level() + 1;
    return out;
}

bool Location::operator==(const Location& obj)
{
    return level_ == obj.level_ && row_ == obj.row_ && column_ == obj.column_;
}

bool Location::operator!=(const Location& obj)
{
    return !(*this == obj);
}

void Location::incLevel()
{
    (++level_)%=8;
}
void Location::incRow()
{
    (++row_)%=8;
}
void Location::incColumn()
{
    (++column_)%=8;
}

void Location::decLevel()
{
    (level_+=7)%=8;
}
void Location::decRow()
{
    (row_+=7)%=8;
}
void Location::decColumn()
{
    (column_+=7)%=8;
}

