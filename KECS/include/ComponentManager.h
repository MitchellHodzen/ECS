#pragma once

#include <bitset>
#include <type_traits>
#include <iostream>

//Forward declarations
struct Position;
struct Velocity;

class ComponentManager
{
public:
	ComponentManager(int maxEntities);
	~ComponentManager();
	enum Components {position, velocity, COMPONENT_COUNT};

	//Template function to add a component 
	template<typename T> void AddComponent(int entityID)
	{
		if constexpr (std::is_same<T, Position>::value)
		{
			if (!entityKeyArray[entityID][Components::position])
			{
				std::cout << "Adding entity " << entityID << "'s Position component" << std::endl;
				entityKeyArray[entityID][Components::position] = true;
			}
		}
		else if constexpr (std::is_same<T, Velocity>::value)
		{
			if (!entityKeyArray[entityID][Components::velocity])
			{
				std::cout << "Adding entity " << entityID << "'s Velocity component" << std::endl;
				entityKeyArray[entityID][Components::velocity] = true;
			}
		}
		else {
			std::cout << "Not a component type" << std::endl;
		}
	}

	template<typename T> void RemoveComponent(int entityID)
	{
		if constexpr (std::is_same<T, Position>::value)
		{
			if (entityKeyArray[entityID][Components::position])
			{
				std::cout << "Removing entity " << entityID << "'s Position component" << std::endl;
				entityKeyArray[entityID][Components::position] = false;
			}
		}
		else if constexpr (std::is_same<T, Velocity>::value)
		{
			if (entityKeyArray[entityID][Components::velocity])
			{
				std::cout << "Removing entity " << entityID << "'s Velocity component" << std::endl;
				entityKeyArray[entityID][Components::velocity] = false;
			}
		}
		else {
			std::cout << "Not a component type" << std::endl;
		}
	}

	void PrintEntityKey(int entityID)
	{
		std::cout << entityID << ": " << entityKeyArray[entityID] << std::endl;
	}
private:
	int maxEntities;
	std::bitset<Components::COMPONENT_COUNT>* entityKeyArray;
	Position* positionComponentArray;
	Velocity* velocityComponentArray;
};

