#include "lib/Duck/DecoyDuck.h"
#include "lib/Duck/MallardDuck.h"
#include "lib/Duck/ModelDuck.h"
#include "lib/Duck/RedheadDuck.h"
#include "lib/Duck/RubberDuck.h"
#include "lib/DuckFunctions.h"
#include <cstdlib>


int main()
{
    MallardDuck mallardDuck;
    mallardDuck.Display();
    mallardDuck.Fly();
    mallardDuck.Fly();
    mallardDuck.Fly();
    mallardDuck.Quack();
    mallardDuck.Dance();

    RedheadDuck redheadDuck;
    redheadDuck.Display();
    redheadDuck.Fly();
    redheadDuck.Quack();
    redheadDuck.Dance();

    RubberDuck rubberDuck;
    rubberDuck.Display();
    rubberDuck.Fly();
    rubberDuck.Quack();
    rubberDuck.Dance();

    DecoyDuck decoyDuck;
    decoyDuck.Display();
    decoyDuck.Fly();
    decoyDuck.Quack();
    decoyDuck.Dance();

    ModelDuck modelDuck;
    modelDuck.Display();
    modelDuck.Fly();

    modelDuck.SetFlyBehavior(CreateFlyWithCounting());
    modelDuck.Fly();

    return EXIT_SUCCESS;
}