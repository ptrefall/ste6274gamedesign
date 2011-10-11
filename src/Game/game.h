#pragma once

#include <types_config.h>
#include <TemplateEventHandler.h>
#include <Protocol/gameprotocol.h>

class GameOptions;
class Client;
class EntityManager;
namespace Components { class Player; }
namespace Systems { class RenderSystem; class MeshSystem; class MaterialSystem; }
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

	void setPlayer(Components::Player &player) { this->player = &player; }

private:
	void parseNetGamePackets();
	void handleNetGameUpdate(const gp_game_update &update);
	void onKeyPressed(const int &key, const unsigned int &modifiers);
	void onKeyReleased(const int &key, const unsigned int &modifiers);
	void onMove(const T_String &x, const T_String &y);

	GameOptions *options;
	Client *client;
	EntityManager *entityMgr;
	Systems::RenderSystem *renderSystem;
	Systems::MeshSystem *meshSystem;
	Systems::MaterialSystem *materialSystem;
	Totem::ComponentFactory *componentFactory;
	Totem::Entity *skybox;

	T_HashedString keyPressedEventId;
	T_HashedString keyReleasedEventId;
	T_HashedString loadMeshEventId;
	T_HashedString loadMaterialEventId;
	T_HashedString moveEventId;

	Components::Player *player;
};
