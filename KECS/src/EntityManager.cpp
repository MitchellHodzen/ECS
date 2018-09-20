#include "EntityManager.h"
#include <iostream>

EntityManager::EntityManager(int maxEntities)
{
	this->maxEntities = maxEntities;

	this->availableEntityIndicies = new Stack<int>(maxEntities);
	for (int i = maxEntities - 1; i >= 0; --i)
	{
		availableEntityIndicies->Push(i);
	}

	this->validEntityIndicies = new bool[maxEntities];
	for (int i = 0; i < maxEntities; ++i)
	{
		validEntityIndicies[i] = false;
	}
}


EntityManager::~EntityManager()
{
	delete availableEntityIndicies;
	delete[] validEntityIndicies;
}

int EntityManager::CreateEntity()
{
	if (entityCount < maxEntities)
	{
		int entityIndex = availableEntityIndicies->Pop();
		SetValidEntityIndex(entityIndex, true);
		if (entityIndex > topEntityIndex)
		{
			topEntityIndex = entityIndex;
		}
		return entityIndex;
	}
	else
	{
		//Return -1 if there are no more available entities
		std::cout << "No more available entities" << std::endl;
		return -1;
	}
}

void EntityManager::DestroyEntity(int entityIndex)
{
	if (IsValidEntityIndex(entityIndex))
	{
		availableEntityIndicies->Push(entityIndex);
		SetValidEntityIndex(entityIndex, false);
	}
	else
	{
		std::cout << "Cannot delete entity: invalid entity index" << std::endl;
	}
}

void EntityManager::PrintValidEntities()
{
	for (int i = 0; i < maxEntities; ++i)
	{
		std::cout << i << ": " << validEntityIndicies[i] << std::endl;
	}
}

void EntityManager::SetValidEntityIndex(int entityIndex, bool value)
{
	validEntityIndicies[entityIndex] = value;
}

bool EntityManager::IsValidEntityIndex(int entityIndex)
{
	if (entityIndex < maxEntities)
	{
		return validEntityIndicies[entityIndex];
	}
	return false;
}

int EntityManager::GetMaxEntities()
{
	return maxEntities;
}

int EntityManager::GetTopEntityIndex()
{
	return topEntityIndex;
}