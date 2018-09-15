#include "ECS.h"
#include "EntityManager.h"
#include <iostream>
#include "Components/c_position.h"
#include"ComponentManager.h"
#include "Components\c_test.h"
#include "System.h"

void PrintEntitiesPosition(int entityIndex) {
	Position pos = ComponentManager::GetComponent<Position>(entityIndex);
	std::cout << "Entity " << entityIndex << "'s Position is: ("<< pos.x << ", "<<pos.y<<")" << std::endl;
}

void PrintEntitiesVelocity(int entityIndex) {
	Velocity vel = ComponentManager::GetComponent<Velocity>(entityIndex);
	std::cout << "Entity " << entityIndex << "'s Velocity is: (" << vel.dx << ", " << vel.dy << ")" << std::endl;
}

void PrintEntitiesPositionAndVelocity(int entityIndex) {
	Position pos = ComponentManager::GetComponent<Position>(entityIndex);
	Velocity vel = ComponentManager::GetComponent<Velocity>(entityIndex);
	std::cout << "Entity " << entityIndex << "'s Position and Velocity is: (" << pos.x << ", " << pos.y << "), (" << vel.dx << ", " << vel.dy << ")" << std::endl;

}
ECS::ECS()
{
	EntityManager em(5);
	ComponentManager::SetUpComponents<Position, Velocity, Test>();
	ComponentManager::em = &em;


	int ent0 = em.CreateEntity();
	int ent1 = em.CreateEntity();
	int ent2 = em.CreateEntity();

	Position* p = ComponentManager::componentArray<Position>;
	ComponentManager::AddComponent<Position>(ent0);
	Position pos = ComponentManager::GetComponent<Position>(ent0);
	pos.x = 50;
	pos.y = 3;
	ComponentManager::SetComponent<Position>(ent0, pos);

	ComponentManager::AddComponent<Velocity>(ent1);

	ComponentManager::AddComponent<Position>(ent2);
	ComponentManager::AddComponent<Velocity>(ent2);

	System::Run<Position>(PrintEntitiesPosition);
	System::Run<Velocity>(PrintEntitiesVelocity);
	System::Run<Position, Velocity>(PrintEntitiesPositionAndVelocity);
}


ECS::~ECS()
{
}


