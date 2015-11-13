#include "WindowManager.h"
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>

WindowManager::WindowManager() {
	windowWidth = 0;
	windowHeight = 0;
	windowPosX = 0;
	windowPosY = 0;
	windowTitle = "";
}


void WindowManager::setWindowDimensions(int w, int h) {
	windowWidth = w;
	windowHeight = h;
}
int WindowManager::getWindowWidth() {
	return windowWidth;
}
int WindowManager::getWindowHeight() {
	return windowHeight;
}


void WindowManager::setWindowPosition(int xPos, int yPos) {
	windowPosX = xPos;
	windowPosY = yPos;
}


void WindowManager::setWindowTitle(std::string str) {
	windowTitle = str;
}


void WindowManager::createWindow(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow(windowTitle.c_str());
}