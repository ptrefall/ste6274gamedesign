#pragma once

#include <types_config.h>
#include <Component.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Game;

namespace Components
{
	class Player : public Totem::Component
	{
	public:
		COMPONENT_1(Player, Game);
		Player(Totem::Entity &owner, const T_String &name, Game &game);
		virtual ~Player();

		virtual void update(const F32 &deltaTime);

		void onKeyPressed(const int &key, const unsigned int &modifiers);
		void onKeyReleased(const int &key, const unsigned int &modifiers);

	private:
		void onPositionChanged(const glm::vec3 &oldValue, const glm::vec3 &newValue);
		void setRollDirection(const float &roll);
		Game &game;
		T_Map<int, bool>::Type key_map;
		Totem::Property<D32> x_dir;
		Totem::Property<D32> y_dir;
		Totem::Property<D32> velocity;
		Totem::Property<glm::gtc::quaternion::quat> qStepPitchRotation;
		Totem::Property<glm::gtc::quaternion::quat> qStepYawRotation;
		Totem::Property<glm::gtc::quaternion::quat> qStepRollRotation;
		Totem::Property<glm::gtc::quaternion::quat> qRotation;
		Totem::Property<glm::vec3> position;
		Totem::Property<glm::vec3> camera_distance;
		float roll_angle;
		float roll_speed;
		float steer_angle;
		float old_steer_angle;
		float turn_speed;

		T_HashedString moveEventId;
	};
}
