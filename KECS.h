#pragma once
#define MAX_ENTITIES 100
#include "Stack.h"
#include <type_traits>
#include <iostream>
#include <vector>

typedef int Entity;

class EntityManager
{
public:
	//Entity related functions
	static Entity CreateEntity()
	{
		if (entityCount < MAX_ENTITIES - 1 && !availableEntityIndicies->IsEmpty())
		{
			int entityIndex = availableEntityIndicies->Pop();
			ComponentManager::ClearEntityComponents(entityIndex);
			TagManager::ClearEntityTags(entityIndex);
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


	static void DestroyEntity(Entity entity)
	{
		if (IsValidEntity(entity))
		{
			ComponentManager::ClearEntityComponents(entity);
			SetValidEntityIndex(entity, false);
			availableEntityIndicies->Push(entity);
		}
		else
		{
			std::cout << "Cannot delete entity: invalid entity" << std::endl;
		}
	}


	static void PrintValidEntities()
	{
		for (int i = 0; i < MAX_ENTITIES; ++i)
		{
			std::cout << i << ": " << validEntityIndicies[i] << std::endl;
		}
	}


	static bool IsValidEntity(int entity)
	{
		if (entity < MAX_ENTITIES)
		{
			return validEntityIndicies[entity];
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
	template<typename T, typename... Args> static void AddComponent(Entity entity)
	{
		if (IsValidEntity(entity))
		{
			ComponentManager::AddComponent<T, Args...>(entity);
		}
		else
		{
			std::cout << "Entity " << entity << " is not a valid entity. Cannot add component" << std::endl;
		}
	}

	//Template function to remove a component 
	template<typename T, typename... Args> static void RemoveComponent(Entity entity)
	{
		if (IsValidEntity(entity))
		{
			ComponentManager::RemoveComponent<T, Args...>(entity);
		}
		else
		{
			std::cout << "Entity " << entity << " is not a valid entity. Cannot remove component" << std::endl;
		}
	}

	//Template function to check if an entity has a component
	template<typename T, typename... Args> static bool HasComponent(Entity entity)
	{
		if (IsValidEntity(entity))
		{
			return ComponentManager::HasComponent<T, Args...>(entity);
		}
		std::cout << "Entity " << entity << " is not a valid entity. Cannot check component" << std::endl;
		return false;
	}

	//Template function to get an entities component 
	template<typename T> static T& GetComponent(Entity entity)
	{
		if (IsValidEntity(entity))
		{
			return ComponentManager::GetComponent<T>(entity);
		}
		std::cout << "Entity " << entity << " is not a valid entity. Cannot get component. Returning nonsense" << std::endl;

	}

	//Template function to set an entities component
	template<typename T> static void SetComponent(Entity entity, T value)
	{
		if (IsValidEntity(entity))
		{
			ComponentManager::SetComponent<T>(entity, value);
		}
	}

	//Template function to get all entities which contain a set of components
	template<typename... Components> static std::vector<Entity> GetEntitiesWithComponent()
	{
		std::vector<Entity> vec;
		for (Entity i = 0; i <= GetTopEntityIndex(); ++i)
		{
			if (IsValidEntity(i) && ComponentManager::HasComponent<Components...>(i))
			{
				vec.push_back(i);
			}
		}
		return vec;
	}

	//Function wrappers for tags
	template<typename T, typename... Args> static void SetUpTags()
	{
		TagManager::SetUpTags<T, Args...>();
	}

	//Template function to add a component 
	template<typename T, typename... Args> static void AddTag(Entity entity)
	{
		if (IsValidEntity(entity))
		{
			TagManager::AddTag<T, Args...>(entity);
		}
		else
		{
			std::cout << "Entity " << entity << " is not a valid entity. Cannot add tag" << std::endl;
		}
	}

	//Template function to remove a component 
	template<typename T, typename... Args> static void RemoveTag(Entity entity)
	{
		if (IsValidEntity(entity))
		{
			TagManager::RemoveTag<T, Args...>(entity);
		}
		else
		{
			std::cout << "Entity " << entity << " is not a valid entity. Cannot remove tag" << std::endl;
		}
	}

	//Template function to check if an entity has a component
	template<typename T, typename... Args> static bool HasTag(Entity entity)
	{
		if (IsValidEntity(entity))
		{
			return TagManager::HasTag<T, Args...>(entity);
		}
		std::cout << "Entity " << entity << " is not a valid entity. Cannot check tag" << std::endl;
		return false;
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

			componentCount = 1 + sizeof...(Args);
			entityComponentKeys = new bool*[MAX_ENTITIES];
			for (int i = 0; i < MAX_ENTITIES; ++i)
			{
				entityComponentKeys[i] = new bool[componentCount];
				for (int j = 0; j < componentCount; ++j)
				{
					entityComponentKeys[i][j] = false;
				}

			}
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
			if (!HasComponent<T>(entityIndex))
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
			if (HasComponent<T>(entityIndex))
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
			return entityComponentKeys[entityIndex][componentIndex<T>];//entityComponentFlags<T>[entityIndex];
		}

		//Template function to get an entities component 
		template<typename T> static T& GetComponent(int entityIndex)
		{
			if (HasComponent<T>(entityIndex))
			{
				return componentArray<T>[entityIndex];
			}
			std::cout << "Entity " << entityIndex << " does not have that component. Cannot get component. Returning nonsense" << std::endl;
		}

		//Template function to set an entities component
		template<typename T> static void SetComponent(int entityIndex, T value)
		{
			if (!HasComponent<T>(entityIndex))
			{
				AddComponent<T>(entityIndex);
			}
			componentArray<T>[entityIndex] = value;

		}

		//Removes all components from a given entity
		static void ClearEntityComponents(int entityIndex)
		{
			for (int i = 0; i < componentCount; ++i)
			{
				entityComponentKeys[entityIndex][i] = false;
			}
		}

	private:

		static inline int componentCount = 0;

		template<typename T> static inline T* componentArray = nullptr;
		template<typename T> static inline int componentIndex = 0;
		static inline bool** entityComponentKeys = nullptr;

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
		}



		//Set the flag for whether an entity has or doesn't have a component
		template<typename T> static void UpdateEntityComponent(int entityIndex, bool value)
		{
			entityComponentKeys[entityIndex][componentIndex<T>] = value;
			//entityComponentFlags<T>[entityIndex] = value;
		}

	};




	//Privately define tag manager. Separate tag related functions to be easier to understand 
	class TagManager
	{
	public:

		template<typename T, typename... Args> static void SetUpTags()
		{

			tagCount = 1 + sizeof...(Args);
			entityTagKeys = new bool*[MAX_ENTITIES];
			for (int i = 0; i < MAX_ENTITIES; ++i)
			{
				entityTagKeys[i] = new bool[tagCount];
				for (int j = 0; j < tagCount; ++j)
				{
					entityTagKeys[i][j] = false;
				}

			}
			SetTagValues<T, Args...>(0);
		}

		//Template function to add a tag
		template<typename T, typename S, typename... Args> static void AddTag(int entityIndex)
		{
			AddTag<T>(entityIndex);
			AddTag<S, Args...>(entityIndex);
		}
		template<typename T> static void AddTag(int entityIndex)
		{
			std::cout << "Adding entity " << entityIndex << "'s " << typeid(T).name() << " tag" << std::endl;
			UpdateEntityTag<T>(entityIndex, true);
		}

		//Template function to remove a tag 
		template<typename T, typename S, typename... Args> static void RemoveTag(int entityIndex)
		{
			RemoveTag<T>(entityIndex);
			RemoveTag<S, Args...>(entityIndex);
		}
		template<typename T> static void RemoveTag(int entityIndex)
		{
			std::cout << "Removing entity " << entityIndex << "'s " << typeid(T).name() << " tag" << std::endl;
			UpdateEntityTag<T>(entityIndex, false);
		}

		//Template function to check if an entity has a tag
		template<typename T, typename S, typename... Args> static bool HasTag(int entityIndex)
		{
			return (HasTag<T>(entityIndex) && HasTag<S, Args...>(entityIndex));
		}
		template<typename T> static bool HasTag(int entityIndex)
		{
			return entityTagKeys[entityIndex][tagIndex<T>];
		}

		//Removes all tags from a given entity
		static void ClearEntityTags(int entityIndex)
		{
			for (int i = 0; i < tagCount; ++i)
			{
				entityTagKeys[entityIndex][i] = false;
			}
		}

	private:
		static inline int tagCount = 0;

		template<typename T> static inline int tagIndex = 0;
		static inline bool** entityTagKeys = nullptr;

		//Template function for setting up tags
		template<typename T, typename S, typename... Args> static void SetTagValues(int index)
		{
			SetTagValues<T>(index);
			SetTagValues<S, Args...>(++index);
		}
		template<typename T> static void SetTagValues(int index)
		{
			tagIndex<T> = index;
		}

		//Set the flag for whether an entity has or doesn't have a tag
		template<typename T> static void UpdateEntityTag(int entityIndex, bool value)
		{
			entityTagKeys[entityIndex][tagIndex<T>] = value;
			//entityComponentFlags<T>[entityIndex] = value;
		}
	};
};

