#include "ECS.h"
#include "EntityManager.h"
#include <iostream>
#include "Components/c_position.h"
#include"ComponentManager.h"
#include "Components\c_test.h"

#define MAX_ENTITIES 10

ECS::ECS()
{
	ComponentManager::SetUpComponents<Position, Velocity>();
	//SetUpComponents<Position, Velocity>();
	//std::cout << "Component Count: " << ComponentManager::GetComponentCount() << std::endl;
	//std::cout << ComponentManager::componentIndex<Test> << std::endl;
	//std::cout << "Component Count: " << ComponentManager::COMPONENT_COUNT << std::endl;
	/*
	Position* t = ComponentManager::componentArray<Position>;

	for (int i = 0; i < MAX_ENTITIES; ++i)
	{
		std::cout << i << ": " << t[i].x << ", " << t[i].y << std::endl;
	}
	std::cout << std::endl;
	Position* o = ComponentManager::componentArray<Position>;
	o[4].x = 500;
	for (int i = 0; i < MAX_ENTITIES; ++i)
	{
		std::cout << i << ": " << t[i].x << ", " << t[i].y << std::endl;
	}
	*/
	EntityManager em(5);
	em.PrintValidEntities();
	std::cout << std::endl;

	int ent1 = em.CreateEntity();
	int ent2 = em.CreateEntity();
	int ent3 = em.CreateEntity();
	ComponentManager::em = &em;

	ComponentManager::AddComponent<Position>(ent1);
	ComponentManager::AddComponent<Velocity>(ent1);
	std::cout << "Ent1 Position: " << ComponentManager::HasComponent<Position>(ent1) << std::endl;
	std::cout << "Ent1 Velocity: " << ComponentManager::HasComponent<Velocity>(ent1) << std::endl;
	ComponentManager::RemoveComponent<Velocity>(ent1);
	std::cout << std::endl;
	std::cout << "Ent1 Position: " << ComponentManager::HasComponent<Position>(ent1) << std::endl;
	std::cout << "Ent1 Velocity: " << ComponentManager::HasComponent<Velocity>(ent1) << std::endl;


	em.PrintValidEntities();

	std::cout << std::endl;
	em.DestroyEntity(ent2);
	em.PrintValidEntities();
	std::cout << std::endl;

	em.CreateEntity();
	em.PrintValidEntities();
	/*
	ComponentManager cm(&em);
	cm.PrintEntityKey(ent1);
	cm.PrintEntityKey(ent2); 
	cm.PrintEntityKey(ent3);
	cm.AddComponent<Position>(ent1);
	cm.AddComponent<Position, Velocity>(ent2);
	cm.AddComponent<Velocity, Position>(ent3);
	cm.AddComponent<Velocity>(10);
	cm.PrintEntityKey(ent1);
	cm.PrintEntityKey(ent2);
	cm.PrintEntityKey(ent3);
	cm.RemoveComponent<Position>(ent2);
	cm.RemoveComponent<Position>(10);
	cm.RemoveComponent<Position, Velocity>(ent3);
	cm.RemoveComponent<Position, Velocity>(ent1);
	cm.PrintEntityKey(ent1);
	cm.PrintEntityKey(ent2);
	cm.PrintEntityKey(ent3);
	*/
	Position* p = ComponentManager::componentArray<Position>;

	for (int i = 0; i < MAX_ENTITIES; ++i)
	{
		std::cout << p[i].x << ", " << p[i].y << std::endl;
	}

	Velocity* v = ComponentManager::componentArray<Velocity>;

	for (int i = 0; i < MAX_ENTITIES; ++i)
	{
		std::cout << v[i].dx << ", " << v[i].dy << std::endl;
	}

	Position* e = ComponentManager::componentArray<Position>;

	for (int i = 0; i < MAX_ENTITIES; ++i)
	{
		std::cout << e[i].x << ", " << e[i].y << std::endl;
	}
}


ECS::~ECS()
{
}
