#ifndef MODELDUCK_H
#define MODELDUCK_H

#include "Duck.h"
#include "Fly/FlyNoWay.h"
#include "Quack/QuackBehavior.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(std::make_unique<FlyNoWay>(), std::make_unique<QuackBehavior>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}

    void SetQuackBehavior(std::unique_ptr<IQuackBehavior> quackBehavior) override
    {
        Duck::SetQuackBehavior(std::move(quackBehavior));
    }

};

#endif
