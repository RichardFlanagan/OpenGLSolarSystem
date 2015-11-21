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


void InputManager::keyboardInputCallback(unsigned char key, int x, int y) {
	switch (key) {
		case 'e': thisInstance->upPressed = true; break;
		case 'q': thisInstance->downPressed = true; break;
		case 'a': thisInstance->leftPressed = true; break;
		case 'd': thisInstance->rightPressed = true; break;
		case 'w': thisInstance->zoomInPressed = true; break;
		case 's': thisInstance->zoomOutPressed = true; break;
	}
}

void InputManager::keyboardInputUpCallback(unsigned char key, int x, int y) {
	switch (key) {
		case 'e': thisInstance->upPressed = false; break;
		case 'q': thisInstance->downPressed = false; break;
		case 'a': thisInstance->leftPressed = false; break;
		case 'd': thisInstance->rightPressed = false; break;
		case 'w': thisInstance->zoomInPressed = false; break;
		case 's': thisInstance->zoomOutPressed = false; break;
	}
}

void InputManager::specialKeyboardInputCallback(int key, int x, int y) {}

void InputManager::specialKeyboardInputUpCallback(int key, int x, int y) {}

void InputManager::bindInputCallbacks() {
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