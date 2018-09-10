#pragma once
class ComponentManager;
class EntityManager;
class Entity
{
public:
	Entity(int index, int id, EntityManager* em, ComponentManager* cm);
	void Destroy();
	void SetIndex(int index);
	int GetIndex();
	int GetId();
	~Entity();
private:
	int index;
	int id;
	ComponentManager* cm;
	EntityManager* em;
};

