#include "Aircraft.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace Components;
using namespace Totem;

Aircraft::Aircraft(Entity &owner, const T_String &name)
: Component(owner, name)
{
	qRotation = owner.addProperty<glm::gtc::quaternion::quat>("Rotation", glm::gtc::quaternion::quat());
}

Aircraft::~Aircraft()
{
}

void Aircraft::update(const F32 &deltaTime)
{
	qRotation = glm::gtc::quaternion::rotate(qRotation.get(), deltaTime * 40.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}