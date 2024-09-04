#ifndef DUCKFUNCTIONS_H
#define DUCKFUNCTIONS_H

#include "Duck.h"

#include <iostream>
#include <functional>

auto CreateFlyWithCounting = []()
    {
    int flightCount = 0;
    return [flightCount]() mutable {
        ++flightCount;
        std::cout << "I'm flying! Flight #" << flightCount << std::endl;
    };
};

auto CreateFlyNoWay = []()
    {
    return []() {};
};

auto CreateQuackNormal = []()
    {
    return []() {
        std::cout << "Quack!" << std::endl;
    };
};

auto CreateSqueak = []()
    {
    return []()
    {
        std::cout << "Squeak!" << std::endl;
    };
};

auto CreateMuteQuack = []()
    {
    return []() {};
};

auto CreateDanceWaltz = []()
    {
    return []()
    {
        std::cout << "I'm dancing waltz!" << std::endl;
    };
};

auto CreateDanceMinuet = []()
    {
    return []()
    {
        std::cout << "I'm dancing minuet!" << std::endl;
    };
};

auto CreateNoDance = []()
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
