#ifndef REDHEADDUCK_H
#define REDHEADDUCK_H

#include "Duck.h"
#include "Fly/FlyWithWings.h"
#include "Quack/QuackBehavior.h"
#include "Dance/MinuetBehavior.h"

class RedheadDuck : public Duck
{
public:
    RedheadDuck()
            : Duck(std::make_unique<FlyWithWings>(), std::make_unique<QuackBehavior>(), std::make_unique<MinuetBehavior>())
    {
    }

    void Display() const override
    {
        std::cout << "I'm redhead duck" << std::endl;
    }

    void SetFlyBehavior(std::unique_ptr<IFlyBehavior> flyBehavior) override
    {
        Duck::SetFlyBehavior(std::move(flyBehavior));
    }

    void SetQuackBehavior(std::unique_ptr<IQuackBehavior> quackBehavior) override
    {
        Duck::SetQuackBehavior(std::move(quackBehavior));
    }

    void SetDanceBehavior(std::unique_ptr<IDanceBehavior> danceBehavior) override
    {
        Duck::SetDanceBehavior(std::move(danceBehavior));
    }

};

#endif