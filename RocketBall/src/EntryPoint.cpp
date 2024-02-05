#include <iostream>
#include "ApplicationHarness.h"

#include "RocketBall.h"


int main()
{
	ApplicationHarness program(new RocketBall());	//Create a new instance of your application type to pass into the harness here.

	program.Run();

	return 0;
}