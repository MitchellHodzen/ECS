#include "ComponentManager.h"
#include "Components/c_position.h"
#include "Components/c_velocity.h"
#include <iostream>

ComponentManager::ComponentManager(EntityManager* em)
{
	//this->em = em;
	//this->maxEntities = em->GetMaxEntities();
}


ComponentManager::~ComponentManager()
{
	//delete[] positionComponentArray;
	//delete[] velocityComponentArray;
}
