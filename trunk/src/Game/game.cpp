#include "Game.h"
#include "GameOptions.h"
#include <Qt/Client/Client.h>
#include <Qt/Client/Packet.h>
#include "EntityManager.h"
#include "Systems\RenderSystem.h"
#include "Systems\MeshSystem.h"
#include "Systems\MaterialSystem.h"
#include <Entity.h>
#include <ComponentFactory.h>
#include "Components\Renderable.h"
#include "Components\TriangleGeometry.h"
#include "Components\MeshGeometry.h"
#include "Components\SkyboxGeometry.h"
#include "Components\IdleSpin.h"
#include "Components\Player.h"
#include "Components\Material.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Game::Game()
	: client(NULL_PTR), entityMgr(NULL_PTR), renderSystem(NULL_PTR), meshSystem(NULL_PTR), materialSystem(NULL_PTR),
	componentFactory(NULL_PTR), skybox(NULL_PTR), options(NULL_PTR), player(NULL_PTR),
	keyPressedEventId("KEY_PRESSED"), keyReleasedEventId("KEY_RELEASED"), 
	loadMeshEventId("LOAD_MESH"), loadMaterialEventId("LOAD_MATERIAL"), moveEventId("MOVE")
{
	this->registerToEvent2<int, unsigned int>(keyPressedEventId).connect(this, &Game::onKeyPressed);
	this->registerToEvent2<int, unsigned int>(keyReleasedEventId).connect(this, &Game::onKeyReleased);
	this->registerToEvent2<T_String, T_String>(moveEventId).connect(this, &Game::onMove);
}

Game::~Game()
{
	if(options) delete options;
	if(client) delete client;
	if(entityMgr) delete entityMgr;
	if(renderSystem) delete renderSystem;
	if(meshSystem) delete meshSystem;
	if(materialSystem) delete materialSystem;
	if(componentFactory) delete componentFactory;
}

void Game::initializeCore()
{
	options = new GameOptions();
	client = new Client(*this);
	entityMgr = new EntityManager();
	renderSystem = new Systems::RenderSystem();
	meshSystem = new Systems::MeshSystem();
	materialSystem = new Systems::MaterialSystem();

	componentFactory = new Totem::ComponentFactory();
	Components::Renderable::RegisterToFactory(*componentFactory);
	Components::TriangleGeometry::RegisterToFactory(*componentFactory);
	Components::MeshGeometry::RegisterToFactory(*componentFactory);
	Components::IdleSpin::RegisterToFactory(*componentFactory);
	Components::Player::RegisterToFactory(*componentFactory);
	Components::Material::RegisterToFactory(*componentFactory);
	Components::SkyboxGeometry::RegisterToFactory(*componentFactory);
}

void Game::initializeGame()
{
	skybox = &entityMgr->create(*componentFactory);
	skybox->addComponent<Systems::RenderSystem>("Renderable", *renderSystem);
	//dummy->addComponent("TriangleGeometry");
	//skybox->addComponent<Systems::MeshSystem>("MeshGeometry", *meshSystem);
	skybox->addComponent<Systems::MaterialSystem>("SkyboxGeometry", *materialSystem);
	//dummy->addComponent("IdleSpin");
	//dummy->getProperty<glm::vec3>("Position") = glm::vec3(0.0f, 0.0f, -800.0f);
	skybox->sendEvent3<T_String,T_String,T_String>(loadMaterialEventId, "../../resources/Skybox/", "Nebulea", ".png");
	
}

void Game::advanceFrame(const F32 &delta)
{
	parseNetGamePackets();
	client->update(delta);
	entityMgr->update(delta);
	renderSystem->compile();
	renderSystem->render();
}

void Game::parseNetGamePackets()
{
	T_Vector<Packet*>::Type packets = client->getParsedGamePackets();
	for(unsigned int i = 0; i < packets.size(); i++)
	{
		Packet *packet = packets[i];
		if(packet->isGamePacket() == false)
			continue; //This shouldn't happen!

		if(packet->isGameUpd())
			handleNetGameUpdate(packet->getGameUpd());
		/*else if(packet->isGameReq())
			handleNetGameRequest(packet->getGameReq());*/
	}
}

void Game::handleNetGameUpdate(const gp_game_update &update)
{
	for(gp_uint32 i = 0; i < update.count; i++)
	{
		const gp_game_object &go = update.list[i];
		const unsigned int &id = go.id;
		const unsigned char &entity_type = go.obj_type;
		T_String type(go.type);
		glm::mat3 transform(go.matrix.getM11(), go.matrix.getM12(), go.matrix.getM13(),
							go.matrix.getM21(), go.matrix.getM22(), go.matrix.getM23(),
							go.matrix.getM31(), go.matrix.getM32(), go.matrix.getM33());
		
		bool entity_exist = entityMgr->updateFromNet(id, transform);

		//If entity doesn't already exist, then add it
		if(entity_exist == false)
		{
			Totem::Entity &entity = entityMgr->create(*componentFactory);
			entity.addComponent<Systems::RenderSystem>("Renderable", *renderSystem);
			entity.addComponent<Systems::MeshSystem>("MeshGeometry", *meshSystem);
			entity.addComponent<Systems::MaterialSystem>("Material", *materialSystem);

			//If this entity is tied to our client id on the server, add the Player component to it.
			if(id == client->getId())
				entity.addComponent<Game>("Player", *this);
			
			entity.addProperty<unsigned int>("Id", 0);
			entity.addProperty<unsigned char>("Type", 0x0);

			entity.getProperty<unsigned int>("Id") = id;
			entity.getProperty<unsigned char>("Type") = entity_type;

			glm::vec3 position = glm::vec3(transform[2][0]*50.0f, transform[2][1]*50.0f, 0.0f); //for now, this only contains position information
			entity.getProperty<glm::vec3>("Position") = position;

			if(entity_type == GP_GAME_OBJECT_TYPE_PLAYER)
			{
				Totem::Property<glm::gtc::quaternion::quat> pitch = entity.getProperty<glm::gtc::quaternion::quat>("StepPitchRotation");
				pitch = glm::gtc::quaternion::rotate(pitch.get(), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

				entity.getProperty<glm::vec3>("Scale") = glm::vec3(0.5f);
				
				entity.sendEvent2<T_String,T_String>(loadMeshEventId, "../../resources/Mesh/Ferox/", "Ferox.3DS");
				entity.sendEvent8<T_String,T_String,T_String,bool,bool,bool,bool,bool>(loadMaterialEventId, "../../resources/Textures/", "FEROX", ".tga", false,false,true,false,false);
			}
			else if(entity_type == GP_GAME_OBJECT_TYPE_WORLD)
			{
				entity.getProperty<glm::vec3>("Scale") = glm::vec3(30.0f);
				entity.sendEvent2<T_String,T_String>(loadMeshEventId, "../../resources/Mesh/Station/", "space_station_0.3DS");
				entity.sendEvent8<T_String,T_String,T_String,bool,bool,bool,bool,bool>(loadMaterialEventId, "../../resources/Textures/", "STAT", ".jpg", false,false,true,false,false);
			}
		}
	}
}

void Game::onKeyPressed(const int &key, const unsigned int &modifiers)
{
	if(player)
		player->onKeyPressed(key, modifiers);
}

void Game::onKeyReleased(const int &key, const unsigned int &modifiers)
{
	if(player)
		player->onKeyReleased(key, modifiers);
}

void Game::onMove(const T_String &x, const T_String &y)
{
	client->onMoveEvent(x,y);
}
