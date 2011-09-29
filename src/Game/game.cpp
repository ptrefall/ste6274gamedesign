#include "Game.h"
#include "GameOptions.h"
#include <Qt/Client/Client.h>
#include <Qt/Client/Packet.h>
#include "EntityManager.h"
#include "Systems\RenderSystem.h"
#include "Systems\MeshSystem.h"
#include <Entity.h>
#include <ComponentFactory.h>
#include "Components\Renderable.h"
#include "Components\TriangleGeometry.h"
#include "Components\MeshGeometry.h"
#include "Components\IdleSpin.h"

Game::Game()
	: client(NULL_PTR), entityMgr(NULL_PTR), renderSystem(NULL_PTR), meshSystem(NULL_PTR), componentFactory(NULL_PTR), dummy(NULL_PTR), options(NULL_PTR)
{
}

Game::~Game()
{
	if(options) delete options;
	if(client) delete client;
	if(entityMgr) delete entityMgr;
	if(renderSystem) delete renderSystem;
	if(meshSystem) delete meshSystem;
	if(componentFactory) delete componentFactory;
}

void Game::initializeCore()
{
	options = new GameOptions();
	client = new Client();
	entityMgr = new EntityManager();
	renderSystem = new Systems::RenderSystem();
	meshSystem = new Systems::MeshSystem();

	componentFactory = new Factotum::ComponentFactory();
	Components::Renderable::RegisterToFactory(*componentFactory);
	Components::TriangleGeometry::RegisterToFactory(*componentFactory);
	Components::MeshGeometry::RegisterToFactory(*componentFactory);
	Components::IdleSpin::RegisterToFactory(*componentFactory);
}

void Game::initializeGame()
{
	dummy = &entityMgr->create(*componentFactory);
	dummy->addComponent<Systems::RenderSystem>("Renderable", *renderSystem);
	//dummy->addComponent("TriangleGeometry");
	dummy->addComponent<Systems::MeshSystem>("MeshGeometry", *meshSystem);
	dummy->addComponent("IdleSpin");
	dummy->sendEvent2<T_String,T_String>(T_HashedString("LOAD_MESH"), "../../resources/Mesh/Ferox/", "Ferox.3DS");
	dummy->getProperty<glm::vec3>("Position") = glm::vec3(0.0f, 0.0f, -800.0f);
}

void Game::advanceFrame(const F32 &delta)
{
	client->update(delta);
	T_Vector<Packet*>::Type packets = client->getParsedGamePackets();
	entityMgr->update(delta);
	renderSystem->compile();
	renderSystem->render();
}
