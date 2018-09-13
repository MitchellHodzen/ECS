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
}


ECS::~ECS()
{
}
