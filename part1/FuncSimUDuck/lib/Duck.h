#ifndef DUCK_H
#define DUCK_H

#include <iostream>
#include <functional>

class Duck
{
public:
    using FlyFunction = std::function<void()>;
    using QuackFunction = std::function<void()>;
    using DanceFunction = std::function<void()>;

    Duck(FlyFunction flyFunc, QuackFunction quackFunc, DanceFunction danceFunc)
            : m_flyFunc(std::move(flyFunc)),
              m_quackFunc(std::move(quackFunc)),
              m_danceFunc(std::move(danceFunc))
    {
    }

    void Fly() { m_flyFunc(); }
    void Quack() { m_quackFunc(); }
    void Dance() { m_danceFunc(); }
    virtual void Display() const = 0;

    void SetFlyBehavior(FlyFunction flyFunc) { m_flyFunc = std::move(flyFunc); }
    void SetQuackBehavior(QuackFunction quackFunc) { m_quackFunc = std::move(quackFunc); }
    void SetDanceBehavior(DanceFunction danceFunc) { m_danceFunc = std::move(danceFunc); }

private:
    FlyFunction m_flyFunc;
    QuackFunction m_quackFunc;
    DanceFunction m_danceFunc;
};

#endif