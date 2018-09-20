#pragma once
#define MAX_ENTITIES 10

#include "Stack.h"
class EntityManager
{
public:

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
		//ComponentManager::COMPONENT_COUNT = 1 + sizeof...(Args);
		//SetComponentValues<T, Args...>(0);
	}


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
};

