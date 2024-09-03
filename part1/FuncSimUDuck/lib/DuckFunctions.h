#ifndef DUCKFUNCTIONS_H
#define DUCKFUNCTIONS_H

#include "Duck.h"

#include <iostream>
#include <functional>

auto FlyWithCounting = []()
    {
    int flightCount = 0;
    return [flightCount]() mutable {
        ++flightCount;
        std::cout << "I'm flying! Flight #" << flightCount << std::endl;
    };
};

auto FlyNoWay = []()
    {
    return []() {};
};

auto QuackNormal = []()
    {
    return []() {
        std::cout << "Quack!" << std::endl;
    };
};

auto Squeak = []()
    {
    return []()
    {
        std::cout << "Squeak!" << std::endl;
    };
};

auto MuteQuack = []()
    {
    return []() {};
};

auto DanceWaltz = []()
    {
    return []()
    {
        std::cout << "I'm dancing waltz!" << std::endl;
    };
};

auto DanceMinuet = []()
    {
    return []()
    {
        std::cout << "I'm dancing minuet!" << std::endl;
    };
};

auto NoDance = []()
    {
    return []() {};
};


void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	std::cout << std::endl;
}

#endif
