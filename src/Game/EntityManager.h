#pragma once

#include <types_config.h>

namespace Factotum { class Entity; class ComponentFactory; }

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void update(const F32 &delta);

	Factotum::Entity &create(Factotum::ComponentFactory &factory);
	void erase(Factotum::Entity *Entity);
	T_Vector<Factotum::Entity*>::Type &getEntities() { return entities; }

protected:
	T_Vector<Factotum::Entity*>::Type entities;
	T_Vector<Factotum::Entity*>::Type pendingDelete;
};
