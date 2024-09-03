#ifndef DECOYDUCK_H
#define DECOYDUCK_H


#include "../Duck.h"
#include "../DuckFunctions.h"
#include <iostream>
#include <memory>


class DecoyDuck : public Duck
{
public:
    DecoyDuck()
            : Duck(FlyNoWay(), MuteQuack(), NoDance())
    {
    }

    void Display() const override
    {
        std::cout << "I'm decoy duck" << std::endl;
    }
};


#endif
