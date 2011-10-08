#pragma once

#include <types_config.h>
#include <TemplateEventHandler.h>

class GameOptions;
class Client;
class EntityManager;
namespace Systems { class RenderSystem; class MeshSystem; }
namespace Totem { class Entity; class ComponentFactory; }

class Game : public Totem::EventHandler
{
public:
	Game();
	~Game();

	void initializeCore();
	void initializeGame();
	void advanceFrame(const F32 &delta);
	GameOptions &getOptions() { return *options; }
	Client &getClient() { return *client; }

private:
	GameOptions *options;
	Client *client;
	EntityManager *entityMgr;
	Systems::RenderSystem *renderSystem;
	Systems::MeshSystem *meshSystem;
	Totem::ComponentFactory *componentFactory;
	Totem::Entity *dummy;
};
