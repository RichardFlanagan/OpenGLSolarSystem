#include <iostream>
#include <GL/freeglut.h>
#include "InputManager.h"

void InputManager::mouseClickCallback(int button, int state, int x, int y) {
	std::cout << "Mouse click: " << button << " " << state << " " << x << " " << y << std::endl;
}
void InputManager::mouseMoveCallback(int x, int y) {
	std::cout << "Mouse move: " << x << " " << y << std::endl;
}
void InputManager::passiveMouseMoveCallback(int x, int y) {
	std::cout << "Passive mouse move: " << x << " " << y << std::endl;
}
void InputManager::keyboardInputCallback(unsigned char key, int x, int y) {
	std::cout << key << "Keyboard: " << x << " " << y << std::endl;
}
void InputManager::specialKeyboardInputCallback(int key, int x, int y) {
	std::cout << "Special Keyboard: " << key << " " << x << " " << y << std::endl;
}

void InputManager::bindInputCallbacks() {
	glutMouseFunc(mouseClickCallback);
	glutMotionFunc(mouseMoveCallback);
	glutPassiveMotionFunc(passiveMouseMoveCallback);
	glutKeyboardFunc(keyboardInputCallback);
	glutSpecialFunc(specialKeyboardInputCallback);
}