#pragma once

#include <types_config.h>
#include "EntityManager.h"
#include <Entity.h>
#include <ComponentFactory.h>

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
	for(unsigned int i = 0; i < entities.size(); i++)
		delete entities[i];
}

bool EntityManager::updateFromNet(const unsigned int &id, const glm::mat3 &transform)
{
	for(unsigned int i = 0; i < entities.size(); i++)
	{
		if(entities[i]->hasProperty("Id") && entities[i]->getProperty<unsigned int>("Id").get() == id)
		{
			Totem::Entity *entity = entities[i];
			glm::vec3 position = glm::vec3(transform[2][0]*50.0f, transform[2][1]*50.0f, 0.0f); //for now, this only contains position information
			entity->getProperty<glm::vec3>("Position") = position;
			return true;
		}
	}
	return false;
}

void EntityManager::update(const F32 &delta)
{
	if(!pendingDelete.empty())
	{
		for(unsigned int i = 0; i < pendingDelete.size(); i++)
		{
			for(unsigned int j = 0; j < entities.size(); j++)
			{
				if(entities[j] == pendingDelete[i])
				{
					//This is a vector element removal trick that's O(1)
					entities[j] = entities.back();
					entities.pop_back();
					break;
				}
			}
			delete pendingDelete[i];
		}
		pendingDelete.clear();
	}

	for(unsigned int i = 0; i < entities.size(); i++)
		entities[i]->updateComponents(delta);
}

Totem::Entity &EntityManager::create(Totem::ComponentFactory &factory)
{
	Totem::Entity *entity = new Totem::Entity(factory, &serializer);
	entities.push_back(entity);
	return *entity;
}

void EntityManager::erase(Totem::Entity *entity)
{
	pendingDelete.push_back(entity);
}
