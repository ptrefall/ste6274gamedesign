#pragma once

#include <types_config.h>
#include <TemplateEventHandler.h>

class Client;
class EntityManager;
namespace Systems { class RenderSystem; }
namespace Factotum { class Entity; class ComponentFactory; }

class Game : public Factotum::EventHandler
{
public:
	Game();
	~Game();

	void initialize();
	void advanceFrame(const F32 &delta);

private:
	Client *client;
	EntityManager *entityMgr;
	Systems::RenderSystem *renderSystem;
	Factotum::ComponentFactory *componentFactory;
	Factotum::Entity *dummy;
};