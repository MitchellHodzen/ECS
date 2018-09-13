#pragma once
#define MAX_ENTITIES 10
//#define COMPONENT_COUNT 3
//try to implement bitset?

//#include <bitset>
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
	enum Components {position, velocity, COMPONENT_COUNT2};

//	static const int COMPONENT_COUNT;

	//static inline int COMPONENT_COUNT;


	template<typename T> static inline T* componentArray = nullptr;
	template<typename T> static inline int componentIndex = 0;
	template<typename T> static inline bool* entityComponentFlags = nullptr;
	/*
	static inline int COMPONENT_COUNT;


	static inline constexpr int GetComponentCount()
	{
		return COMPONENT_COUNT;
	};
	*/

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
		if (em->IsValidEntityIndex(entityIndex) && !HasComponent<T>(entityIndex))//!entityKeyArray[entityIndex][componentIndex<T>])
		{
			std::cout << "Adding entity " << entityIndex << "'s " << typeid(T).name() << " component" << std::endl;
			//entityKeyArray[entityIndex][componentIndex<T>] = true;
			UpdateEntityComponent<T>(entityIndex, true);
			//positionComponentArray[entityIndex].x = 0;
			//positionComponentArray[entityIndex].y = 0;
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
		if (em->IsValidEntityIndex(entityIndex) && HasComponent<T>(entityIndex))//entityKeyArray[entityIndex][componentIndex<T>])
		{
			std::cout << "Removing entity " << entityIndex << "'s " << typeid(T).name() << " component" << std::endl;
			//entityKeyArray[entityIndex][componentIndex<T>] = false;
			UpdateEntityComponent<T>(entityIndex, false);
		}
	}

	//Template function to check if an entity has a component
	template<typename T, typename S, typename... Args> static bool HasComponent(int entityIndex)
	{
		return (HasComponent<T>(entityIndex) && HasComponent<S, Args...>(entityIndex));
	}

	template<typename T> static void UpdateEntityComponent(int entityIndex, bool value)
	{
		entityComponentFlags<T>[entityIndex] = value;
	}

	template<typename T> static bool HasComponent(int entityIndex)
	{
		if (em->IsValidEntityIndex(entityIndex))
		{
			return entityComponentFlags<T>[entityIndex];
		}
		return false;
	}


	/*
	void PrintEntityKey(int entityIndex)
	{
		std::cout << entityIndex << ": " << entityKeyArray[entityIndex] << std::endl;
	}
	*/
	static inline EntityManager* em;

private:
	//std::bitset<std::as_const<const int>(COMPONENT_COUNT)>* entityKeyArray = new std::bitset<const_cast<COMPONENT_COUNT>>[MAX_ENTITIES];
	//static inline void* entityKeyArray;


	//template<int SIZE> static inline std::bitset<SIZE>* entityKeyArray; 
	//template<int T> static inline const int COMPONENT_COUNT = T;
	
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
};