#include "Game.h"
#include "GameOptions.h"
#include <Qt/Client/Client.h>
#include "EntityManager.h"
#include "Systems\RenderSystem.h"
#include <Entity.h>
#include <ComponentFactory.h>
#include "Components\Renderable.h"
#include "Components\TriangleRenderer.h"

Game::Game()
	: client(NULL_PTR), entityMgr(NULL_PTR), renderSystem(NULL_PTR), componentFactory(NULL_PTR), dummy(NULL_PTR), options(NULL_PTR)
{
}

Game::~Game()
{
	if(options) delete options;
	if(client) delete client;
	if(entityMgr) delete entityMgr;
	if(renderSystem) delete renderSystem;
	if(componentFactory) delete componentFactory;
}

void Game::initialize()
{
	options = new GameOptions();
	client = new Client();
	entityMgr = new EntityManager();
	renderSystem = new Systems::RenderSystem();
	componentFactory = new Factotum::ComponentFactory();
	Components::Renderable::RegisterToFactory(*componentFactory);
	Components::TriangleRenderer::RegisterToFactory(*componentFactory);

	dummy = &entityMgr->create(*componentFactory);
	dummy->addComponent<Systems::RenderSystem>("Renderable", *renderSystem);
	dummy->addComponent("TriangleRenderer");
}

void Game::advanceFrame(const F32 &delta)
{
	entityMgr->update(delta);
	renderSystem->compile();
	renderSystem->render();
}
