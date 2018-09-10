#include "ECS.h"
#include "EntityManager.h"
#include <iostream>
#include "Components/c_position.h"
#include"ComponentManager.h"


ECS::ECS()
{

	EntityManager em(5);
	em.PrintValidEntities();
	std::cout << std::endl;

	int ent1 = em.CreateEntity();
	int ent2 = em.CreateEntity();
	int ent3 = em.CreateEntity();
	em.PrintValidEntities();

	std::cout << std::endl;
	em.DestroyEntity(ent2);
	em.PrintValidEntities();
	std::cout << std::endl;

	em.CreateEntity();
	em.PrintValidEntities();

	ComponentManager cm(&em);
	cm.PrintEntityKey(ent1);
	cm.PrintEntityKey(ent2);
	cm.PrintEntityKey(ent3);
	cm.AddComponent<Position>(ent1);
	cm.AddComponent<Position>(ent2);
	cm.AddComponent<Velocity>(ent2);
	cm.AddComponent<Velocity>(10);
	cm.PrintEntityKey(ent1);
	cm.PrintEntityKey(ent2);
	cm.PrintEntityKey(ent3);
	cm.RemoveComponent<Position>(ent2);
	cm.RemoveComponent<Position>(10);
	cm.PrintEntityKey(ent1);
	cm.PrintEntityKey(ent2);
	cm.PrintEntityKey(ent3);
}


ECS::~ECS()
{
}
