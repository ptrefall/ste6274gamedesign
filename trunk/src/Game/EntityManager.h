#pragma once

#include <types_config.h>
#include <glm/glm.hpp>
#include <PropertySerializer.h>

namespace Totem { class Entity; class ComponentFactory; }

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void update(const F32 &delta);

	bool updateFromNet(const unsigned int &id, const glm::mat3 &transform);

	Totem::Entity &create(Totem::ComponentFactory &factory);
	void erase(Totem::Entity *Entity);
	T_Vector<Totem::Entity*>::Type &getEntities() { return entities; }

protected:
	T_Vector<Totem::Entity*>::Type entities;
	T_Vector<Totem::Entity*>::Type pendingDelete;
	Totem::PropertySerializer serializer;
};
