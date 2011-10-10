#include "Player.h"
#include <Game\game.h>
#include <Game\Camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <qevent.h>

using namespace Components;
using namespace Totem;

Player::Player(Entity &owner, const T_String &name, Game &game)
: Component(owner, name), game(game), moveEventId("MOVE")
{
	//Fill keymap with supported keys
	key_map[Qt::Key_Up] = false;
	key_map[Qt::Key_Down] = false;
	key_map[Qt::Key_Left] = false;
	key_map[Qt::Key_Right] = false;

	x_dir = owner.addProperty<D32>("XDir", 0.0);
	y_dir = owner.addProperty<D32>("YDir", 0.0);
	velocity = owner.addProperty<D32>("Velocity", 10.0);
	position = owner.addProperty<glm::vec3>("Position", glm::vec3(0.0f));
	position.valueChanged().connect(this, &Player::onPositionChanged);

	camera_distance = owner.addProperty<glm::vec3>("CameraDistance", glm::vec3(0.0f, 0.0f, 5000.0f));
	Camera::setPos(position.get()+camera_distance.get());

	game.setPlayer(*this);
}

Player::~Player()
{
}

void Player::update(const F32 &deltaTime)
{
	//reset
	x_dir = 0.0;
	y_dir = 0.0;

	if(key_map[Qt::Key_Up])
		y_dir += 1.0;
	
	if(key_map[Qt::Key_Down])
		y_dir -= 1.0;

	if(key_map[Qt::Key_Left])
		x_dir -= 1.0;

	if(key_map[Qt::Key_Right])
		x_dir += 1.0;

	x_dir *= velocity.get() * (D32)deltaTime;
	y_dir *= velocity.get() * (D32)deltaTime;

	//There was a move!
	if(x_dir.get() != 0.0 || y_dir.get() != 0.0)
		game.sendEvent2<T_String, T_String>(moveEventId, x_dir.toString(), y_dir.toString());
}

void Player::onKeyPressed(const int &key, const unsigned int &modifiers)
{
	key_map[key] = true;
}

void Player::onKeyReleased(const int &key, const unsigned int &modifiers)
{
	key_map[key] = false;
}

void Player::onPositionChanged(const glm::vec3 &oldValue, const glm::vec3 &newValue)
{
	Camera::setPos(newValue+camera_distance.get());
}
