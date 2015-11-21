#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <assert.h>

#include "ShaderManager.h"
#include "ModelLoader.h"
#include "RenderManager.h"
#include "LightingManager.h"
#include "Camera.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "VBO.h"


int main(int argc, char** argv) {
	// WindowManager
	WindowManager windowManager;
	windowManager.setWindowDimensions(800, 600);
	windowManager.setWindowPosition(100, 100);
	windowManager.setWindowTitle("A00193644 : Solar System");
	windowManager.createWindow(argc, argv);
	
	// GLEW
	GLenum res = glewInit();
	assert(res == GLEW_OK);

	// VertexBufferObject
	VBO sphere("assets/sphere.obj");
	sphere.loadModel();

	// ShaderManager
	ShaderManager shaderManager;
	shaderManager.loadShaders();
	
	// LightingManager
	LightingManager lightingManager(&shaderManager);
	lightingManager.setAmbientLightIntensity(glm::vec3(0.2f));
	lightingManager.setDirectionalLightDirection(glm::vec3(1.0f, 0.0f, 0.0f)); //(0.0f, 0.0f, -1.0f));
	lightingManager.setDirectionalLightIntensity(glm::vec3(0.7f));
	lightingManager.setSpecularLightIntensity(glm::vec3(0.9f));
	lightingManager.updateUniformVariables();

	// InputManager
	InputManager inputManager;
	inputManager.bindInputCallbacks();

	// CameraManager
	Camera camera(&inputManager, &windowManager);
	camera.setCameraSpeed(1.0f);
	camera.setViewPlanes(1.0f, 1000.0f);
	camera.setPosition(glm::vec3(0.0f, 20.0f, 40.0f));
	camera.setViewAngle(45.0f);

	// RenderManager
	RenderManager renderManager(&shaderManager, &camera, &windowManager, &sphere);
	renderManager.setRenderOptions(60);
	renderManager.bindDisplayCallbacks();
	
	// Main loop
	glutMainLoop();

	return 0;
}