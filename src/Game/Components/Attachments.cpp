#include "Attachments.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace Components;
using namespace Totem;

Attachments::Attachments(Entity &owner, const T_String &name)
: Component(owner, name)
{
	attachments = owner.addPropertyList<Totem::Entity*>("Attachments");
	attachments.valueAdded().connect(this, &Attachments::onValueAdded);

	position = owner.addProperty<glm::vec3>("Position", glm::vec3(0.0f));
	position.valueChanged().connect(this, &Attachments::onPositionChanged);

	/*modelMatrix = owner.addProperty<glm::mat4>("ModelMatrix", glm::mat4(1.0f));
	modelMatrix.valueChanged().connect(this, &Attachments::onModelMatrixChanged);*/

	/*qStepYawRotation = owner.addProperty<glm::gtc::quaternion::quat>("StepYawRotation", glm::gtc::quaternion::quat());
	qStepYawRotation.valueChanged().connect(this, &Attachments::onStepYawRotationChanged);*/
}

Attachments::~Attachments()
{
}

void Attachments::onValueAdded(const U32 &index, Totem::Entity *const &newValue)
{
	/*if(newValue->hasProperty("StepYawRotation"))
	{
		Totem::Property<glm::gtc::quaternion::quat> yaw = newValue->getProperty<glm::gtc::quaternion::quat>("StepYawRotation");
		yaw = qStepYawRotation.get();
	}*/

	if(newValue->hasProperty("Position"))
	{
		Totem::Property<glm::vec3> pos = newValue->getProperty<glm::vec3>("Position");
			
		if(newValue->hasProperty("Offset"))
		{
			Totem::Property<glm::vec3> offset = newValue->getProperty<glm::vec3>("Offset");
			pos = position.get() + offset.get();
		}
		else
		{
			pos = position.get();
		}
	}
}

void Attachments::onPositionChanged(const glm::vec3 &oldValue, const glm::vec3 &newValue)
{
	for(U32 i = 0; i < attachments.size(); i++)
	{
		Totem::Entity *attachment = attachments[i].get();
		if(attachment->hasProperty("Position"))
		{
			Totem::Property<glm::vec3> pos = attachment->getProperty<glm::vec3>("Position");
			
			if(attachment->hasProperty("Offset"))
			{
				Totem::Property<glm::vec3> offset = attachment->getProperty<glm::vec3>("Offset");
				pos = newValue + offset.get();
			}
			else
			{
				pos = newValue;
			}
		}
	}
}


/*void Attachments::onModelMatrixChanged(const glm::mat4 &oldValue, const glm::mat4 &newValue)
{
	for(U32 i = 0; i < attachments.size(); i++)
	{
		Totem::Entity *attachment = attachments[i].get();
		if(attachment->hasProperty("InheritedModelMatrix"))
		{
			Totem::Property<glm::mat4> model = attachment->getProperty<glm::mat4>("InheritedModelMatrix");
			model = newValue;
		}
	}
}*/

/*void Attachments::onStepYawRotationChanged(const glm::gtc::quaternion::quat &oldValue, const glm::gtc::quaternion::quat &newValue)
{
	for(U32 i = 0; i < attachments.size(); i++)
	{
		Totem::Entity *attachment = attachments[i].get();
		if(attachment->hasProperty("StepYawRotation"))
		{
			Totem::Property<glm::gtc::quaternion::quat> yaw = attachment->getProperty<glm::gtc::quaternion::quat>("StepYawRotation");
			yaw = newValue;
		}
	}
}*/
