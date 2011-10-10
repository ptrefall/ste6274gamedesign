#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Totem { class Entity; }

class Camera
{
public:
	static glm::mat4 getPerspective();
	static glm::mat4 getView();

	static void prepare();
	static void rotate(const float &rate, const glm::vec3 &axis);
	static void translate(const glm::vec3 &delta_pos);
	static void setPos(const glm::vec3 &pos);

private:
	static glm::vec3 position;
	static glm::gtc::quaternion::quat qRotation;
	static glm::mat4 view;
};
