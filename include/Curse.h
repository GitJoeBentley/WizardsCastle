#ifndef CURSE_H
#define CURSE_H
#include <string>

class Curse
{
public:
    Curse(int num);
    virtual ~Curse();
    void apply();
    static const std::string name[4];

protected:

private:
    int number;
    int wardingTeasure;
};

#endif // CURSE_H
