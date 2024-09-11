#ifndef RUBBERDUCK_H
#define RUBBERDUCK_H

#include "Duck.h"
#include "Fly/FlyNoWay.h"
#include "Quack/SqueakBehavior.h"
#include <iostream>

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(std::make_unique<FlyNoWay>(), std::make_unique<SqueakBehavior>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}

    void SetQuackBehavior(std::unique_ptr<IQuackBehavior> quackBehavior) override
    {
        Duck::SetQuackBehavior(std::move(quackBehavior));
    }
};

#endif
