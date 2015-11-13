#include "Camera.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "InputManager.h"
#include "WindowManager.h"


Camera::Camera(InputManager* im, WindowManager* wm) {
	inputManager = im;
	windowManager = wm;
	
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

	speed = 1.0f;
	viewAngle = 0.0f;
	nearViewPlane = 1.0f;
	farViewPlane = 100.0f;
}


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


glm::mat4 Camera::getWorldToViewMatrix() const {
	return glm::lookAt(
			position,
			target,
			upDirection
		);
}


glm::mat4 Camera::getProjectionMatrix() const {
	return glm::perspective(
			viewAngle,
			(float) windowManager->getWindowWidth() / (float) windowManager->getWindowWidth(),
			nearViewPlane,
			farViewPlane
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


glm::vec3 Camera::getPosition() const {
	return position;
}
glm::vec3 Camera::getTarget() const {
	return target;
}
glm::vec3 Camera::getUpDirection() const {
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

void Camera::setCameraSpeed(float sp) {
	speed = sp;
}
void Camera::setViewPlanes(float nvPlane, float fvPlane) {
	nearViewPlane = nvPlane;
	farViewPlane = fvPlane;
}
void Camera::setViewAngle(float angle) {
	viewAngle = angle;
}