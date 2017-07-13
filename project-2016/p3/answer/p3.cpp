#include <iostream>
#include "world_type.h"
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
	try 
	{
		simulation::Controller controller(argc, argv);
		controller.readSpecies(argv[1]);
		controller.readWorld(argv[2]);
		controller.simulate();
	}
	catch (simulation::MyException e)
	{
		cout << e.what() << endl;
	}
	//cin.get();
	return 0;
}