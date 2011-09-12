#pragma once

#include <Component.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Components
{
	class IdleSpin : public Factotum::Component
	{
	public:
		COMPONENT_0(IdleSpin);
		IdleSpin(Factotum::Entity &owner, const T_String &name);
		virtual ~IdleSpin();

		virtual void update(const F32 &deltaTime);

	private:
		Factotum::Property<glm::gtc::quaternion::quat> qRotation;
	};
}
