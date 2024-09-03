#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H


#include "../Duck.h"
#include "../DuckFunctions.h"

class MallardDuck : public Duck
{
public:
    MallardDuck()
            : Duck(FlyWithCounting(), QuackNormal(), DanceWaltz())
    {
    }

    void Display() const override
    {
        std::cout << "I'm mallard duck" << std::endl;
    }
};

#endif