#include "Entity.h"
#include "ComponentManager.h"
#include "EntityManager.h"


Entity::Entity(int index, int id, EntityManager* em, ComponentManager* cm)
{
	this->index = index;
	this->id = id;
	this->em = em;
	this->cm = cm;
}


Entity::~Entity()
{
}

void Entity::Destroy() 
{
	em->DestroyEntity(this->index);
}

void Entity::SetIndex(int index)
{
	this->index = index;
}

int Entity::GetIndex()
{
	return this->index;
}

int Entity::GetId()
{
	return this->id;
}