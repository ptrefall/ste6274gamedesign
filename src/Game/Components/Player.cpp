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
	velocity = owner.addProperty<D32>("Velocity", 20.0);
	qRotation = owner.addProperty<glm::gtc::quaternion::quat>("Rotation", glm::gtc::quaternion::quat());
	qStepPitchRotation = owner.addProperty<glm::gtc::quaternion::quat>("StepPitchRotation", glm::gtc::quaternion::quat());
	qStepYawRotation = owner.addProperty<glm::gtc::quaternion::quat>("StepYawRotation", glm::gtc::quaternion::quat());
	qStepRollRotation = owner.addProperty<glm::gtc::quaternion::quat>("StepRollRotation", glm::gtc::quaternion::quat());
	position = owner.addProperty<glm::vec3>("Position", glm::vec3(0.0f));
	position.valueChanged().connect(this, &Player::onPositionChanged);

	camera_distance = owner.addProperty<glm::vec3>("CameraDistance", glm::vec3(0.0f, 0.0f, 5000.0f));
	Camera::setPos(position.get()+camera_distance.get());

	game.setPlayer(*this);

	roll_angle = 0.0f;
	roll_speed = 15.0f;
	turn_speed = 15.0f;
	steer_angle = 0.0f;
	old_steer_angle = 0.0f;
}

Player::~Player()
{
}

void Player::update(const F32 &deltaTime)
{
	//reset
	x_dir = 0.0;
	y_dir = 0.0;
	D32 velocity_step = 0.0;
	S32 rolling_direction = 0;

	if(key_map[Qt::Key_Up])
		velocity_step += 1.0;
	
	if(key_map[Qt::Key_Down])
		velocity_step -= 1.0;

	if(key_map[Qt::Key_Left])
		rolling_direction += 1;

	if(key_map[Qt::Key_Right])
		rolling_direction -= 1;

	if(rolling_direction != 0)
	{
		roll_angle += roll_speed * rolling_direction * deltaTime;

		while(roll_angle > 360.0f)
			roll_angle -= 360.0f;
		while(roll_angle < 0.0f)
			roll_angle += 360.0f;
	}
	else
		roll_angle = 0.0f;

	float steer_angle_rad = 0.0f;

	if(roll_angle >= 0.0f && roll_angle < 90.0f)
	{
		steer_angle += -roll_angle * deltaTime * turn_speed;
		steer_angle_rad = glm::core::function::trigonometric::radians(steer_angle);
	}
	else if(roll_angle >= 90.0f && roll_angle < 180.0f)
	{
		steer_angle += -(180 - roll_angle) * deltaTime * turn_speed;
		steer_angle_rad = glm::core::function::trigonometric::radians(steer_angle);
	}
	else if(roll_angle >= 180.0f && roll_angle < 270.0f)
	{
		steer_angle -= -(roll_angle - 180) * deltaTime * turn_speed;
		steer_angle_rad = glm::core::function::trigonometric::radians(steer_angle);
	}
	else if(roll_angle > 270.0f && roll_angle < 360.0f)
	{
		steer_angle -= -(360 - roll_angle) * deltaTime * turn_speed;
		steer_angle_rad = glm::core::function::trigonometric::radians(steer_angle);
	}

	D32 xf = (D32)glm::sin(steer_angle_rad);
	D32 yf = (D32)glm::cos(steer_angle_rad);

	velocity_step *= velocity.get() * (D32)deltaTime;

	x_dir = xf * velocity_step;
	y_dir = yf * velocity_step;

	float delta_steer_angle = steer_angle - old_steer_angle;
	old_steer_angle = steer_angle;
	if(delta_steer_angle != 0.0f)
	{
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		qStepYawRotation = glm::gtc::quaternion::rotate(qStepYawRotation.get(), delta_steer_angle, up);
	}

	/*if(roll_angle != 0.0f)
	{
		glm::vec3 forward = (qStepYawRotation.get() * qStepPitchRotation.get() * qStepRollRotation.get()) * glm::vec3(0.0f, 0.0f, -1.0f);
		qStepRollRotation = glm::gtc::quaternion::rotate(qStepRollRotation.get(), roll_angle, forward);
	}*/

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

void Player::setRollDirection(const float &roll)
{

}
