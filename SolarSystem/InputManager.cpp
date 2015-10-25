#include "InputManager.h"
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>


InputManager* InputManager::thisInstance = nullptr;

InputManager::InputManager() {
	upPressed = false;
	downPressed = false;
	leftPressed = false;
	rightPressed = false;
	zoomInPressed = false;
	zoomOutPressed = false;

	thisInstance = this;
};

void InputManager::mouseClickCallback(int button, int state, int x, int y) {
	if (state == 0) {
		switch (button) {
			case 0: std::cout << "Left" << std::endl; break; // Left click
			case 1: std::cout << "Middle" << std::endl; break; // Middle click
			case 2: std::cout << "Right" << std::endl; break;  // Right click
			case 3: std::cout << "Scroll up" << std::endl; break;  // Scroll up click
			case 4: std::cout << "Scroll down" << std::endl; break;  // Scroll down click
		}
	}
}
void InputManager::mouseMoveCallback(int x, int y) {
	/*std::cout << "Mouse move: " << x << " " << y << std::endl;
	std::cout << "Orig pos: " << instance->camera->getPosition().x << " " << instance->camera->getPosition().y << " " << instance->camera->getPosition().z << std::endl;
	int xOffset = x-instance->camera->getPosition().x;
	int yOffset = y-instance->camera->getPosition().y;
	std::cout << "Difference: " << xOffset << " " << yOffset <<std::endl;
	instance->camera->orbit(glm::vec3((float)xOffset, (float)yOffset, 0.0f));
	std::cout << "New pos: " << instance->camera->getPosition().x << " " << instance->camera->getPosition().y << " " << instance->camera->getPosition().z << std::endl << std::endl;*/

	/*static float mousePressX = x;
	static float mousePressY = y;

	float xOffset = mousePressX - x;
	float yOffset = mousePressY - y;
	
	
	std::cout << "Orig pos: " << instance->camera->getPosition().x << " " << instance->camera->getPosition().y << " " << instance->camera->getPosition().z << std::endl;
	instance->camera->move(glm::vec3(xOffset*0.001f, yOffset*0.001f, 0.0f));
	
	std::cout << "New pos:  " << instance->camera->getPosition().x << " " << instance->camera->getPosition().y << " " << instance->camera->getPosition().z << std::endl;
	std::cout << "Difference: " << xOffset << " " << yOffset << std::endl << std::endl;
	
	//prevX = instance->camera->getPosition().x;
	//prevY = instance->camera->getPosition().y;*/
}
void InputManager::passiveMouseMoveCallback(int x, int y) {}

void InputManager::keyboardInputCallback(unsigned char key, int x, int y) {
	switch (key) {
		case 'w': thisInstance->upPressed = true; break;
		case 's': thisInstance->downPressed = true; break;
		case 'a': thisInstance->leftPressed = true; break;
		case 'd': thisInstance->rightPressed = true; break;
		case 'e': thisInstance->zoomInPressed = true; break;
		case 'q': thisInstance->zoomOutPressed = true; break;
	}
}

void InputManager::keyboardInputUpCallback(unsigned char key, int x, int y) {
	switch (key) {
		case 'w': thisInstance->upPressed = false; break;
		case 's': thisInstance->downPressed = false; break;
		case 'a': thisInstance->leftPressed = false; break;
		case 'd': thisInstance->rightPressed = false; break;
		case 'e': thisInstance->zoomInPressed = false; break;
		case 'q': thisInstance->zoomOutPressed = false; break;
	}
}

void InputManager::specialKeyboardInputCallback(int key, int x, int y) {}

void InputManager::specialKeyboardInputUpCallback(int key, int x, int y) {}

void InputManager::bindInputCallbacks() {
	glutMouseFunc(thisInstance->mouseClickCallback);
	glutMotionFunc(thisInstance->mouseMoveCallback);
	glutPassiveMotionFunc(thisInstance->passiveMouseMoveCallback);
	glutKeyboardFunc(thisInstance->keyboardInputCallback);
	glutKeyboardUpFunc(thisInstance->keyboardInputUpCallback);
	glutSpecialFunc(thisInstance->specialKeyboardInputCallback);
	glutSpecialUpFunc(thisInstance->specialKeyboardInputUpCallback);
}

const bool InputManager::isUpPressed() {
	return upPressed;
}
const bool InputManager::isDownPressed() {
	return downPressed;
}
const bool InputManager::isLeftPressed() {
	return leftPressed;
}
const bool InputManager::isRightPressed() {
	return rightPressed;
}
const bool InputManager::isZoomInPressed() {
	return zoomInPressed;
}
const bool InputManager::isZoomOutPressed() {
	return zoomOutPressed;
}