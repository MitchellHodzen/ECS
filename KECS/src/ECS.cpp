#include "ECS.h"
#include "EntityManager.h"
#include <iostream>
#include "Components/c_position.h"
#include"ComponentManager.h"
#include "Components\c_test.h"

ECS::ECS()
{
	EntityManager em(5);
	ComponentManager::SetUpComponents<Position, Velocity>();
	ComponentManager::em = &em;


	int ent0 = em.CreateEntity();
	int ent1 = em.CreateEntity();
	int ent2 = em.CreateEntity();

	Position* p = ComponentManager::componentArray<Position>;
	ComponentManager::AddComponent<Position>(ent0);
	for (int i = 0; i < MAX_ENTITIES; ++i)
	{
		std::cout << i << ": (" << p[i].x << ", " << p[i].y << ")" << std::endl;
	}
	std::cout << std::endl;
	Position pos = ComponentManager::GetComponent<Position>(ent0);
	pos.x = 50;
	pos.y = 3;
	for (int i = 0; i < MAX_ENTITIES; ++i)
	{
		std::cout << i << ": (" << p[i].x << ", " << p[i].y << ")" << std::endl;
	}
	std::cout << std::endl;
	ComponentManager::SetComponent<Position>(ent0, pos);
	for (int i = 0; i < MAX_ENTITIES; ++i)
	{
		std::cout << i << ": (" << p[i].x << ", " << p[i].y << ")" << std::endl;
	}
	std::cout << std::endl;
	ComponentManager::RemoveComponent<Position>(ent0);
	ComponentManager::AddComponent<Position>(ent0);
	for (int i = 0; i < MAX_ENTITIES; ++i)
	{
		std::cout << i << ": (" << p[i].x << ", " << p[i].y << ")" << std::endl;
	}
	std::cout << std::endl;

	
}


ECS::~ECS()
{
}
