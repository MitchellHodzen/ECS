#pragma once
//#define COMPONENT_COUNT 3
//try to implement bitset?

//#include <bitset>
#include <type_traits>
#include <iostream>
#include "EntityManager.h"
#include "Components/c_position.h"
#include "Components/c_velocity.h"
#include <vector>

class ComponentManager
{
public:

	static inline EntityManager* em;

	template<typename T, typename... Args> static void SetUpComponents()
	{
		//ComponentManager::COMPONENT_COUNT = 1 + sizeof...(Args);
		SetComponentValues<T, Args...>(0);
	}


	//Template function to add a component 
	template<typename T, typename S, typename... Args> static void AddComponent(int entityIndex)
	{
		AddComponent<T>(entityIndex);
		AddComponent<S, Args...>(entityIndex);
	}
	template<typename T> static void AddComponent(int entityIndex)
	{
		if (em->IsValidEntityIndex(entityIndex) && !HasComponent<T>(entityIndex))
		{
			std::cout << "Adding entity " << entityIndex << "'s " << typeid(T).name() << " component" << std::endl;
			UpdateEntityComponent<T>(entityIndex, true);
			//Reset the component to default values
			componentArray<T>[entityIndex] = T();
		}
	}

	//Template function to remove a component 
	template<typename T, typename S, typename... Args> static void RemoveComponent(int entityIndex)
	{
		RemoveComponent<T>(entityIndex);
		RemoveComponent<S, Args...>(entityIndex);
	}
	template<typename T> static void RemoveComponent(int entityIndex)
	{
		if (em->IsValidEntityIndex(entityIndex) && HasComponent<T>(entityIndex))
		{
			std::cout << "Removing entity " << entityIndex << "'s " << typeid(T).name() << " component" << std::endl;
			UpdateEntityComponent<T>(entityIndex, false);
		}
	}

	//Template function to check if an entity has a component
	template<typename T, typename S, typename... Args> static bool HasComponent(int entityIndex)
	{
		return (HasComponent<T>(entityIndex) && HasComponent<S, Args...>(entityIndex));
	}
	template<typename T> static bool HasComponent(int entityIndex)
	{
		if (em->IsValidEntityIndex(entityIndex))
		{
			return entityComponentFlags<T>[entityIndex];
		}
		return false;
	}

	template<typename... Components> static std::vector<int> GetEntitiesWithComponent()
	{
		std::vector<int> vec;
		for (int i = 0; i <= em->GetTopEntityIndex(); ++i)
		{
			if (em->IsValidEntityIndex(i) && HasComponent<Components...>(i))
			{
				vec.push_back(i);
			}
		}
		return vec;
	}

	//Template function to get an entities component 
	template<typename T> static T GetComponent(int entityIndex)
	{
		if (em->IsValidEntityIndex(entityIndex) && HasComponent<T>(entityIndex))
		{
			return componentArray<T>[entityIndex];
		}
	}

	//Template function to set an entities component
	template<typename T> static void SetComponent(int entityIndex, T value)
	{
		if (em->IsValidEntityIndex(entityIndex) && HasComponent<T>(entityIndex))
		{
			componentArray<T>[entityIndex] = value;
		}
	}
	template<typename T> static inline T* componentArray = nullptr;

private:
	ComponentManager() {};
	~ComponentManager() {};
	//std::bitset<std::as_const<const int>(COMPONENT_COUNT)>* entityKeyArray = new std::bitset<const_cast<COMPONENT_COUNT>>[MAX_ENTITIES];
	
	template<typename T> static inline int componentIndex = 0;
	template<typename T> static inline bool* entityComponentFlags = nullptr;

	//Template function for setting up components
	template<typename T, typename S, typename... Args> static void SetComponentValues(int index)
	{
		SetComponentValues<T>(index);
		SetComponentValues<S, Args...>(++index);
	}
	template<typename T> static void SetComponentValues(int index)
	{
		componentIndex<T> = index;
		componentArray<T> = new T[MAX_ENTITIES];
		entityComponentFlags<T> = new bool[MAX_ENTITIES];
		for (int i = 0; i < MAX_ENTITIES; ++i)
		{
			entityComponentFlags<T>[i] = false;
		}
	}

	//Set the flag for whether an entity has or doesn't have a component
	template<typename T> static void UpdateEntityComponent(int entityIndex, bool value)
	{
		entityComponentFlags<T>[entityIndex] = value;
	}
};