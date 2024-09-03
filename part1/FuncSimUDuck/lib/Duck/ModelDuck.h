#ifndef MODELDUCK_H
#define MODELDUCK_H


#include "../Duck.h"
#include "../DuckFunctions.h"

class ModelDuck : public Duck
{
public:
    ModelDuck()
            : Duck(FlyNoWay(), QuackNormal(), NoDance())
    {
    }

    void Display() const override
    {
        std::cout << "I'm model duck" << std::endl;
    }
};


#endif
