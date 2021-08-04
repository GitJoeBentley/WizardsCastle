#ifndef BOOK_H
#define BOOK_H

#include <Room.h>


class Book : public Room
{
public:
    Book();
    std::string description() const
    {
        return "book";
    }
};

#endif // BOOK_H
