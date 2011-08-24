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

Factotum::Entity &EntityManager::create(Factotum::ComponentFactory &factory)
{
	Factotum::Entity *entity = new Factotum::Entity(factory);
	entities.push_back(entity);
	return *entity;
}

void EntityManager::erase(Factotum::Entity *entity)
{
	pendingDelete.push_back(entity);
}
