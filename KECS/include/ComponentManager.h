#pragma once

#include <bitset>
#include <type_traits>
#include <iostream>
#include "EntityManager.h"
#include "Components/c_position.h"
#include "Components/c_velocity.h"



class ComponentManager
{
public:
	ComponentManager(EntityManager* em);
	~ComponentManager();
	enum Components {position, velocity, COMPONENT_COUNT};

	//Template function to add a component 
	template<typename T, typename S, typename... Args> void AddComponent(int entityIndex)
	{
		AddComponent<T>(entityIndex);
		AddComponent<S, Args...>(entityIndex);
	}
	template<typename T> void AddComponent(int entityIndex)
	{
		if constexpr (std::is_same<T, Position>::value)
		{
			if (em->IsValidEntityIndex(entityIndex) && !entityKeyArray[entityIndex][Components::position])
			{
				std::cout << "Adding entity " << entityIndex << "'s Position component" << std::endl;
				entityKeyArray[entityIndex][Components::position] = true;
				positionComponentArray[entityIndex].x = 0;
				positionComponentArray[entityIndex].y = 0;
			}
		}
		else if constexpr (std::is_same<T, Velocity>::value)
		{
			if (em->IsValidEntityIndex(entityIndex) && !entityKeyArray[entityIndex][Components::velocity])
			{
				std::cout << "Adding entity " << entityIndex << "'s Velocity component" << std::endl;
				entityKeyArray[entityIndex][Components::velocity] = true;
				velocityComponentArray[entityIndex].dx = 0;
				velocityComponentArray[entityIndex].dy = 0;
			}
		}
		else {
			std::cout << "Not a component type" << std::endl;
		}
	}

	//Template function to remove a component 
	template<typename T, typename S, typename... Args> void RemoveComponent(int entityIndex)
	{
		RemoveComponent<T>(entityIndex);
		RemoveComponent<S, Args...>(entityIndex);
	}
	template<typename T> void RemoveComponent(int entityIndex)
	{
		if constexpr (std::is_same<T, Position>::value)
		{
			if (em->IsValidEntityIndex(entityIndex) && entityKeyArray[entityIndex][Components::position])
			{
				std::cout << "Removing entity " << entityIndex << "'s Position component" << std::endl;
				entityKeyArray[entityIndex][Components::position] = false;
			}
		}
		else if constexpr (std::is_same<T, Velocity>::value)
		{
			if (em->IsValidEntityIndex(entityIndex) && entityKeyArray[entityIndex][Components::velocity])
			{
				std::cout << "Removing entity " << entityIndex << "'s Velocity component" << std::endl;
				entityKeyArray[entityIndex][Components::velocity] = false;
			}
		}
		else {
			std::cout << "Not a component type" << std::endl;
		}
	}

	void PrintEntityKey(int entityIndex)
	{
		std::cout << entityIndex << ": " << entityKeyArray[entityIndex] << std::endl;
	}
private:
	int maxEntities;
	std::bitset<Components::COMPONENT_COUNT>* entityKeyArray;
	Position* positionComponentArray;
	Velocity* velocityComponentArray;
	EntityManager* em;
};

