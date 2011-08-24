#include "Game.h"
#include "EntityManager.h"
#include "Systems\RenderSystem.h"
#include <Entity.h>
#include <ComponentFactory.h>
#include "Components\Renderable.h"

Game::Game()
	: entityMgr(NULL_PTR), renderSystem(NULL_PTR), componentFactory(NULL_PTR), dummy(NULL_PTR)
{
}

Game::~Game()
{
	if(entityMgr) delete entityMgr;
	if(renderSystem) delete renderSystem;
	if(componentFactory) delete componentFactory;
}

void Game::initialize()
{
	entityMgr = new EntityManager();
	renderSystem = new Systems::RenderSystem();
	componentFactory = new Factotum::ComponentFactory();
	Components::Renderable::RegisterToFactory(*componentFactory);

	dummy = &entityMgr->create(*componentFactory);
	dummy->addComponent<Systems::RenderSystem>("Renderable", *renderSystem);
}

void Game::advanceFrame(const F32 &delta)
{
	entityMgr->update(delta);
	renderSystem->render();
}
