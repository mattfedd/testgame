#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Includes.h"
#include "Components.h"
#include <typeinfo>
//#include "Entity.h"

class EntityManager;

class Entity
{
private:
	unsigned int ID;
	EntityManager* em;

public:
	Entity() : em(NULL) {
	for(int i=0; i<NUM_COMPONENTS; ++i)
		{
			components[i] = 0xffff;
			inUse[i] = false;
		}
	}
	Entity(EntityManager* m) : em(m) 
	{
		for(int i=0; i<NUM_COMPONENTS; ++i)
		{
			components[i] = 0xffff;
			inUse[i] = false;
		}
	}
	~Entity() {}

	void setId(unsigned int i) { ID=i; }
	unsigned int getId() { return ID; }

	template <typename T>
	void addComponent(T& t) 
	{
		unsigned int index = T::getId();
		if(components[index] <= NUM_COMPONENTS)
		{
			LOGES("Container", "ERROR: Tried adding duplicate component type to a single entity");
		}
		else
		{
			components[index]= em->addComponent(this, t);
			inUse[index] = true;
		}
	}
	
	unsigned int components[NUM_COMPONENTS];
	bool inUse[NUM_COMPONENTS];
};

class ContainerBase
{
public:
	~ContainerBase() {}
	virtual void add() {}
};

template <typename T>
class Container : public ContainerBase
{
private:
	bool inUse[CONTAINER_SIZE];
	T data[CONTAINER_SIZE];
	unsigned int firstEmptyIndex;

	unsigned int findFirstEmptyIndex()
	{
		for(int i=0; i<CONTAINER_SIZE; ++i)
		{
			if(!inUse[i])
				return i;
		}
		return CONTAINER_SIZE;
	}

public:
	Container() : firstEmptyIndex(0) 
	{
		for (int i=0; i<CONTAINER_SIZE; ++i)
		{
			inUse[i] = false;
		}
	}

	~Container() {}

	//returns the index of the added item in the array
	unsigned int add(T t)
	{
		inUse[firstEmptyIndex] = true;
		data[firstEmptyIndex] = t;
		int ret = firstEmptyIndex;
		if(firstEmptyIndex++ > CONTAINER_SIZE || inUse[firstEmptyIndex])
		{
			firstEmptyIndex = findFirstEmptyIndex();
		}
		return ret;
	}

	//sets the inUse index to false
	void remove(unsigned int index)
	{
		inUse[index] = false;
		if(firstEmptyIndex >index)
			firstEmptyIndex = index;
	}

	//returns a reference to the item
	T& get(unsigned int index)
	{
		if(inUse[index])
			return data[index];
		else
			return T();
	}

	unsigned int size()
	{
		return CONTAINER_SIZE;
	}
};


class EntityManager
{
private:
	Container<Entity> entities;

	std::vector<ContainerBase*> components;


public:
	EntityManager() 
	{
		//push all component arrays into the vector in their order as given in Includes.h
		components.resize(NUM_COMPONENTS);
		components[POSITION_ID] = new Container<PositionComponent>();
		components[HEALTH_ID] = new Container<HealthComponent>();
		components[VELOCITY_ID] = new Container<VelocityComponent>();
		components[SPRITE_ID] = new Container<SpriteComponent>();
		components[COLLISION_ID] = new Container<CollisionComponent>();
		components[PHYSICS_ID] = new Container<PhysicsComponent>();
		components[TEXT_ID] = new Container<TextComponent>();
	}
	~EntityManager() {}
	
	//returns reference to created entity
	Entity& createEntity() 
	{
		Entity& o = Entity(this);
		unsigned int index = entities.add(o);
		entities.get(index).setId(index);
		return entities.get(index);
	}

	template <typename T>
	unsigned int addComponent(Entity* e, T& t)
	{
		return static_cast<Container<T> *>(components[T::getId()])->add(t);
	}

	template <typename T>
	Container<T>*  getComponentVector()
	{
		return static_cast<Container<T> *>(components[T::getId()]);
	}

	Container<Entity>& getEntities()
	{
		return entities;
	}

};


#endif 