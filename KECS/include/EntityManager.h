#pragma once
#include "Stack.h"
class Entity;

class EntityManager
{
public:
	EntityManager(int maxEntities);
	~EntityManager();
	int CreateEntity();
	void DestroyEntity(int entityIndex);
	void PrintValidEntities();
	bool IsValidEntityIndex(int entityIndex);
	int GetMaxEntities();
	int GetTopEntityIndex();
private:
	int maxEntities = 0;
	int topEntityIndex = 0;
	Stack<int>* availableEntityIndicies;
	bool* validEntityIndicies;
	int entityCount = 0;
	void SetValidEntityIndex(int entityIndex, bool value);
};

