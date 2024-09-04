#ifndef REDHEADDUCK_H
#define REDHEADDUCK_H

#include "../Duck.h"
#include "../DuckFunctions.h"

class RedheadDuck : public Duck
{
public:
    RedheadDuck()
            : Duck(CreateFlyWithCounting(), CreateQuackNormal(), CreateDanceMinuet())
    {
    }

    void Display() const override
    {
        std::cout << "I'm redhead duck" << std::endl;
    }
};

#endif