#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
	Camera() {
		position = glm::vec3(0.0f, 0.0f, 10.0f);
		target = glm::vec3(0.0f, 0.0f, 0.0f);
		upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
	};
	const glm::mat4 getWorldToViewMatrix();

	void move(glm::vec3 offset);
	void orbit(glm::vec3 offset);
	void look(glm::vec3 offset);

	const glm::vec3 getPosition();
	const glm::vec3 getTarget();
	const glm::vec3 getUpDirection();
	
	void setPosition(glm::vec3 vector);
	void setTarget(glm::vec3 vector);
	void setUpDirection(glm::vec3 vector);
private:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 upDirection;
};
#endif // CAMERA_H