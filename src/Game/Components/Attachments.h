#pragma once

#include <Component.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Components
{
	class Attachments : public Totem::Component
	{
	public:
		COMPONENT_0(Attachments);
		Attachments(Totem::Entity &owner, const T_String &name);
		virtual ~Attachments();

	private:
		Totem::PropertyList<Totem::Entity*> attachments;
		void onValueAdded(const U32 &index, Totem::Entity *const &newValue);

		Totem::Property<glm::vec3> position;
		void onPositionChanged(const glm::vec3 &oldValue, const glm::vec3 &newValue);
		/*Totem::Property<glm::mat4> modelMatrix;
		void onModelMatrixChanged(const glm::mat4 &oldValue, const glm::mat4 &newValue);*/

		/*Totem::Property<glm::gtc::quaternion::quat> qStepYawRotation;
		void onStepYawRotationChanged(const glm::gtc::quaternion::quat &oldValue, const glm::gtc::quaternion::quat &newValue);*/
	};
}
