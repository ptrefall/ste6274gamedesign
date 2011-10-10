#include "Camera.h"
#include <Entity.h>
#include <Game/Graphics/Utils.h>

glm::vec3 Camera::position = glm::vec3(0.0f);
glm::gtc::quaternion::quat Camera::qRotation = glm::gtc::quaternion::quat();
glm::mat4 Camera::view = glm::mat4(1.0f);

void Camera::rotate(const float &rate, const glm::vec3 &axis)
{
	qRotation = glm::gtc::quaternion::rotate(qRotation, rate, axis);
}
void Camera::translate(const glm::vec3 &delta_pos)
{
	position += delta_pos;
}

void Camera::setPos(const glm::vec3 &pos)
{
	position = pos;
}

void Camera::prepare()
{
	glm::mat4 translate = glm::mat4(1.0f);
	translate[3][0] = -position.x;
	translate[3][1] = -position.y;
	translate[3][2] = -position.z;

	glm::mat4 rotation = glm::gtc::quaternion::mat4_cast(qRotation);

	view = glm::mat4(1.0f);
	view *= translate;
	view *= rotation;
}

glm::mat4 Camera::getPerspective()
{
	GLdouble p[16];
	glGetDoublev(GL_PROJECTION_MATRIX, p);
	return glm::mat4(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],p[11],p[12],p[13],p[14],p[15]);
}

glm::mat4 Camera::getView()
{
	//GLdouble v[16];
	//glGetDoublev(GL_MODELVIEW_MATRIX, v);
	//return glm::mat4(v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],v[10],v[11],v[12],v[13],v[14],v[15]);
	return view;
}
