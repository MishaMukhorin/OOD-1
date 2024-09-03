#ifndef FUNCTIONALDUCK_H
#define FUNCTIONALDUCK_H

#include "../Duck.h"
#include "../DuckFunctions.h"
#include <memory>

class FunctionalDuck
{
public:
    using FlyFunction = std::function<void()>;
    using QuackFunction = std::function<void()>;
    using DanceFunction = std::function<void()>;

    FunctionalDuck(FlyFunction flyFunc, QuackFunction quackFunc, DanceFunction danceFunc)
            : m_flyFunc(std::move(flyFunc)),
              m_quackFunc(std::move(quackFunc)),
              m_danceFunc(std::move(danceFunc))
    {
    }

    void Fly() { m_flyFunc(); }
    void Quack() { m_quackFunc(); }
    void Dance() { m_danceFunc(); }
    void Display() const { std::cout << "I'm a functional duck" << std::endl; }

private:
    FlyFunction m_flyFunc;
    QuackFunction m_quackFunc;
    DanceFunction m_danceFunc;
};

#endif //OOD_1_FUNCTIONALDUCK_H
