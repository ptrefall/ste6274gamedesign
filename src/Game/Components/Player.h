#pragma once

#include <Component.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Components
{
	class Player : public Totem::Component
	{
	public:
		COMPONENT_0(Player);
		Player(Totem::Entity &owner, const T_String &name);
		virtual ~Player();

		virtual void update(const F32 &deltaTime);

	private:
		Totem::Property<glm::gtc::quaternion::quat> qRotation;
	};
}
