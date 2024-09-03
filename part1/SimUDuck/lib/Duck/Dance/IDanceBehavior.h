#ifndef IDANCEBEHAVIOR_H
#define IDANCEBEHAVIOR_H

struct IDanceBehavior
{
    virtual ~IDanceBehavior() = default;
    virtual void Dance() const = 0;
};

#endif