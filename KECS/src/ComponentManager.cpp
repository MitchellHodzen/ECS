#include "ComponentManager.h"
#include "Components/c_position.h"
#include "Components/c_velocity.h"

ComponentManager::ComponentManager(int maxEntities)
{
	this->maxEntities = maxEntities;
	entityKeyArray = new std::bitset<Components::COMPONENT_COUNT>[maxEntities];
	positionComponentArray = new Position[maxEntities];
	velocityComponentArray = new Velocity[maxEntities];
}


ComponentManager::~ComponentManager()
{
	delete[] positionComponentArray;
	delete[] velocityComponentArray;
}
