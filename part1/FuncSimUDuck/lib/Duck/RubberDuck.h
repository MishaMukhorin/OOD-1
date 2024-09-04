#ifndef RUBBERDUCK_H
#define RUBBERDUCK_H

#include "../Duck.h"
#include "../DuckFunctions.h"
#include <iostream>


class RubberDuck : public Duck
{
public:
    RubberDuck()
            : Duck(CreateFlyNoWay(), CreateSqueak(), CreateNoDance())
    {
    }

    void Display() const override
    {
        std::cout << "I'm rubber duck" << std::endl;
    }
};


#endif
