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
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	PlayWithDuck(redheadDuck);
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
    // ��������� ����� �������
    PlayWithDuck(modelDuck);

	return EXIT_SUCCESS;
}