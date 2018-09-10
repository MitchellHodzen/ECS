#pragma once

class EntityManager
{
public:
	EntityManager(int maxEntities);
	~EntityManager();
	int GetEntity();
	void DestroyEntity(int entityID);
private:
	int maxEntities;
};

