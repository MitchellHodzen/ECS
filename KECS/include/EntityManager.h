#pragma once
#define MAX_ENTITIES 10
#include "Stack.h"

#include <type_traits>
#include <iostream>
#include "EntityManager.h"
#include "Components/c_position.h"
#include "Components/c_velocity.h"
#include <vector>

class EntityManager
{
public:
	//Entity related functions
	static int CreateEntity()
	{
		if (entityCount < MAX_ENTITIES)
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


	static void DestroyEntity(int entityIndex)
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


	static void PrintValidEntities()
	{
		for (int i = 0; i < MAX_ENTITIES; ++i)
		{
			std::cout << i << ": " << validEntityIndicies[i] << std::endl;
		}
	}


	static bool IsValidEntityIndex(int entityIndex)
	{
		if (entityIndex < MAX_ENTITIES)
		{
			return validEntityIndicies[entityIndex];
		}
		return false;
	}

	static int GetTopEntityIndex()
	{
		return topEntityIndex;
	}


	//Component manager wrappers
	template<typename T, typename... Args> static void SetUpComponents()
	{
		//Set up avaiable entities
		availableEntityIndicies = new Stack<int>(MAX_ENTITIES);
		for (int i = MAX_ENTITIES - 1; i >= 0; --i)
		{
			availableEntityIndicies->Push(i);
		}

		//Set up valid indicies
		validEntityIndicies = new bool[MAX_ENTITIES];
		for (int i = 0; i < MAX_ENTITIES; ++i)
		{
			validEntityIndicies[i] = false;
		}

		ComponentManager::SetUpComponents<T, Args...>();
	}

	//Template function to add a component 
	template<typename T, typename... Args> static void AddComponent(int entityIndex)
	{
		ComponentManager::AddComponent<T, Args...>(entityIndex);
	}

	//Template function to remove a component 
	template<typename T, typename... Args> static void RemoveComponent(int entityIndex)
	{
		ComponentManager::RemoveComponent<T, Args...>(entityIndex);
	}

	//Template function to check if an entity has a component
	template<typename T, typename... Args> static bool HasComponent(int entityIndex)
	{
		return ComponentManager::HasComponent<T, Args...>(entityIndex);
	}

	//Template function to get an entities component 
	template<typename T> static T GetComponent(int entityIndex)
	{
		return ComponentManager::GetComponent<T>(entityIndex);
	}

	//Template function to set an entities component
	template<typename T> static void SetComponent(int entityIndex, T value)
	{
		ComponentManager::SetComponent<T>(entityIndex, value);
	}


	template<typename... Components> static std::vector<int> GetEntitiesWithComponent()
	{
		return ComponentManager::GetEntitiesWithComponent<Components...>();
	}

private:
	EntityManager() {};
	~EntityManager() {};
	static inline int topEntityIndex = 0;
	static inline Stack<int>* availableEntityIndicies = nullptr;
	static inline bool* validEntityIndicies = nullptr;
	static inline int entityCount = 0;
	static void SetValidEntityIndex(int entityIndex, bool value)
	{
		validEntityIndicies[entityIndex] = value;
	}

	//Privately define component manager. Separate component related functions to be easier to understand 
	class ComponentManager
	{
	public:


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
			if (EntityManager::IsValidEntityIndex(entityIndex) && !HasComponent<T>(entityIndex))
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
			if (EntityManager::IsValidEntityIndex(entityIndex) && HasComponent<T>(entityIndex))
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
			if (EntityManager::IsValidEntityIndex(entityIndex))
			{
				return entityComponentFlags<T>[entityIndex];
			}
			return false;
		}

		template<typename... Components> static std::vector<int> GetEntitiesWithComponent()
		{
			std::vector<int> vec;
			for (int i = 0; i <= EntityManager::GetTopEntityIndex(); ++i)
			{
				if (EntityManager::IsValidEntityIndex(i) && HasComponent<Components...>(i))
				{
					vec.push_back(i);
				}
			}
			return vec;
		}

		//Template function to get an entities component 
		template<typename T> static T GetComponent(int entityIndex)
		{
			if (EntityManager::IsValidEntityIndex(entityIndex) && HasComponent<T>(entityIndex))
			{
				return componentArray<T>[entityIndex];
			}
		}

		//Template function to set an entities component
		template<typename T> static void SetComponent(int entityIndex, T value)
		{
			if (EntityManager::IsValidEntityIndex(entityIndex) && HasComponent<T>(entityIndex))
			{
				componentArray<T>[entityIndex] = value;
			}
		}

	private:
		ComponentManager() {};
		~ComponentManager() {};
		//std::bitset<std::as_const<const int>(COMPONENT_COUNT)>* entityKeyArray = new std::bitset<const_cast<COMPONENT_COUNT>>[MAX_ENTITIES];

		template<typename T> static inline T* componentArray = nullptr;
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
};

