#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

void Camera::move(glm::vec3 offset) {
	position = position + offset;
	target = target + offset;
}
void Camera::orbit(glm::vec3 offset) {
	position = position + offset;
}
void Camera::look(glm::vec3 offset) {
	target = target + offset;
}
const glm::mat4 Camera::getWorldToViewMatrix() {
	return glm::lookAt(
		position,
		target,
		upDirection
		);
}
void Camera::update() {
	if (inputManager->isUpPressed()) {
		move(glm::vec3(0.0f, speed, 0.0f));
	} 
	if (inputManager->isDownPressed()) {
		move(glm::vec3(0.0f, -speed, 0.0f));
	}
	if (inputManager->isLeftPressed()) {
		move(glm::vec3(-speed, 0.0f, 0.0f));
	}
	if (inputManager->isRightPressed()) {
		move(glm::vec3(speed, 0.0f, 0.0f));
	}
	if (inputManager->isZoomInPressed()) {
		move(glm::vec3(0.0f, 0.0f, -speed));
	}
	if (inputManager->isZoomOutPressed()) {
		move(glm::vec3(0.0f, 0.0f, speed));
	}
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