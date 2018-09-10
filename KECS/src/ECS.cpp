#include "ECS.h"
#include "EntityManager.h"
#include <iostream>
#include "Components/c_position.h"
#include"ComponentManager.h"


ECS::ECS()
{
	ComponentManager cm(10);
	cm.AddComponent<Position>(0);
	cm.AddComponent<Velocity>(1);
	cm.AddComponent<Position>(1);
	cm.PrintEntityKey(0);
	cm.PrintEntityKey(1);
	cm.RemoveComponent<Position>(1);
	cm.PrintEntityKey(1);
}


ECS::~ECS()
{
}
