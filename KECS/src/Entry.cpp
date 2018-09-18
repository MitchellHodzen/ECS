#include <iostream>
#include "ECS.h"
#include "Example.h"
int main(int argc, char *argv[])
{
	ECS ecs;
	Example exec(800, 600);
	exec.Run();
	std::cin.get();
	return 0;
}