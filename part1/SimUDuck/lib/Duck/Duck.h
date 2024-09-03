#ifndef DUCK_H
#define DUCK_H

#include "Fly/IFlyBehavior.h"
#include "Quack/IQuackBehavior.h"
#include "Dance/IDanceBehavior.h"
#include <memory>

class Duck
{
public:
    Duck(std::unique_ptr<IFlyBehavior> flyBehavior,
         std::unique_ptr<IQuackBehavior> quackBehavior,
         std::unique_ptr<IDanceBehavior> danceBehavior = nullptr)
            : m_flyBehavior(std::move(flyBehavior)),
              m_quackBehavior(std::move(quackBehavior)),
              m_danceBehavior(std::move(danceBehavior))
    {
    }

    virtual ~Duck() = default;

    void PerformFly()
    {
        if (m_flyBehavior)
        {
            m_flyBehavior->Fly();
        }
    }

    void PerformQuack()
    {
        if (m_quackBehavior)
        {
            m_quackBehavior->Quack();
        }
    }

    void PerformDance() const
    {
        if (m_danceBehavior)
        {
            m_danceBehavior->Dance();
        }
    }

    virtual void Display() const = 0;

    void SetFlyBehavior(std::unique_ptr<IFlyBehavior> flyBehavior)
    {
        m_flyBehavior = std::move(flyBehavior);
    }

    void SetQuackBehavior(std::unique_ptr<IQuackBehavior> quackBehavior)
    {
        m_quackBehavior = std::move(quackBehavior);
    }

    void SetDanceBehavior(std::unique_ptr<IDanceBehavior> danceBehavior)
    {
        m_danceBehavior = std::move(danceBehavior);
    }

private:
    std::unique_ptr<IFlyBehavior> m_flyBehavior;
    std::unique_ptr<IQuackBehavior> m_quackBehavior;
    std::unique_ptr<IDanceBehavior> m_danceBehavior;
};

#endif
