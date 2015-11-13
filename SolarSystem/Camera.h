/*
File: Camera.h
Author: Richard Flanagan
Description:
*/
#ifndef CAMERA_H
#define CAMERA_H
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "InputManager.h"
#include "WindowManager.h"

class Camera {
public:
	Camera(InputManager* im, WindowManager* wm);
	~Camera() {};

	glm::mat4 getWorldToViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	void update();

	void move(glm::vec3 offset);
	void orbit(glm::vec3 offset);
	void look(glm::vec3 offset);

	glm::vec3 getPosition() const;
	void setPosition(glm::vec3 vector);

	glm::vec3 getTarget() const;
	void setTarget(glm::vec3 vector);

	glm::vec3 getUpDirection() const;
	void setUpDirection(glm::vec3 vector);

	void setCameraSpeed(float sp);
	void setViewAngle(float angle);
	void setViewPlanes(float nvPlane, float fvPlane);
private:
	InputManager* inputManager; 
	WindowManager* windowManager;

	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 upDirection;

	float speed;
	float viewAngle;
	float nearViewPlane;
	float farViewPlane;
};
#endif // CAMERA_H