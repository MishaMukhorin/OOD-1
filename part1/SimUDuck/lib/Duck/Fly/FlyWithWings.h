#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings : public IFlyBehavior
{
public:
    FlyWithWings() : m_flightCount(0) {}

    void Fly() override
    {
        ++m_flightCount;
        std::cout << "I'm flying with wings!! Flight #" << m_flightCount << std::endl;
    }

private:
    int m_flightCount;
};

#endif
