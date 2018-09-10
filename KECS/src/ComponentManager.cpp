#include "ComponentManager.h"
#include "Components/c_position.h"
#include "Components/c_velocity.h"
#include <iostream>

ComponentManager::ComponentManager(EntityManager* em)
{
	this->em = em;
	this->maxEntities = em->GetMaxEntities();
	entityKeyArray = new std::bitset<Components::COMPONENT_COUNT>[maxEntities];
	positionComponentArray = new Position[maxEntities];
	velocityComponentArray = new Velocity[maxEntities];
}


ComponentManager::~ComponentManager()
{
	delete[] positionComponentArray;
	delete[] velocityComponentArray;
}


int ComponentManager::componentIndexCounter = 0;
