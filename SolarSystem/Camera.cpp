#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

void Camera::move(glm::vec3 offset) {
	position = position + offset;
	target = position + offset;
}
void Camera::orbit(glm::vec3 offset) {
	position = position + offset;
}
void Camera::look(glm::vec3 offset) {
	target = position + offset;
}
const glm::mat4 Camera::getWorldToViewMatrix() {
	return glm::lookAt(
		position,
		target,
		upDirection
		);
}

const glm::vec3 Camera::getPosition() {
	return position;
}
const glm::vec3 Camera::getTarget() {
	return target;
}
const glm::vec3 Camera::getUpDirection() {
	return upDirection;
}

void Camera::setPosition(glm::vec3 vector) {
	position = vector;
}
void Camera::setTarget(glm::vec3 vector) {
	target = vector;
}
void Camera::setUpDirection(glm::vec3 vector) {
	upDirection = vector;
}