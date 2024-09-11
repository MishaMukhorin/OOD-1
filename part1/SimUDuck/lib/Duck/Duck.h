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

    void Fly()
    {
        if (m_flyBehavior)
        {
            m_flyBehavior->Fly();
        }
    }

    void Quack()
    {
        if (m_quackBehavior)
        {
            m_quackBehavior->Quack();
        }
    }

    void Dance() const
    {
        if (m_danceBehavior)
        {
            m_danceBehavior->Dance();
        }
    }

    virtual void Display() const = 0;

protected:

    virtual void SetFlyBehavior(std::unique_ptr<IFlyBehavior> flyBehavior) // сделать возможность изменения стратегии только у тех уток которые могут это сделать
    {
        m_flyBehavior = std::move(flyBehavior);
    }

    virtual void SetQuackBehavior(std::unique_ptr<IQuackBehavior> quackBehavior)
    {
        m_quackBehavior = std::move(quackBehavior);
    }

    virtual void SetDanceBehavior(std::unique_ptr<IDanceBehavior> danceBehavior)
    {
        m_danceBehavior = std::move(danceBehavior);
    }

private:
    std::unique_ptr<IFlyBehavior> m_flyBehavior;
    std::unique_ptr<IQuackBehavior> m_quackBehavior;
    std::unique_ptr<IDanceBehavior> m_danceBehavior;
};

#endif
