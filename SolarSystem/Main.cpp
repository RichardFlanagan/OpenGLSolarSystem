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


int windowWidth = 800;
int windowHeight = 600;
int windowOffsetX = 100;
int windowOffsetY = 100;
std::string windowTitle = "A00193644 : Solar System";

int framesPerSecond = 60;
float cameraSpeed = 1.9f;
glm::vec3 cameraPosition = glm::vec3(0.0f, 20.0f, 40.0f);
std::string model = "assets/sphere.obj";

glm::vec3 ambient = glm::vec3(0.1f);
glm::vec3 diffuse = glm::vec3(0.8f);
glm::vec3 specular = glm::vec3(0.9f);


int main(int argc, char** argv) {
	// WindowManager
	WindowManager windowManager;
	windowManager.setWindowDimensions(windowWidth, windowHeight);
	windowManager.setWindowPosition(windowOffsetX, windowOffsetY);
	windowManager.setWindowTitle(windowTitle.c_str());
	windowManager.createWindow(argc, argv);
	
	// GLEW
	GLenum res = glewInit();
	assert(res == GLEW_OK);

	// VertexBufferObject
	VBO sphere(model);
	sphere.loadModel();

	// ShaderManager
	ShaderManager shaderManager;
	shaderManager.loadShaders();
	
	// LightingManager
	LightingManager lightingManager(&shaderManager);
	lightingManager.setAmbientLightIntensity(ambient);
	lightingManager.setDiffuseLightIntensity(diffuse);
	lightingManager.setSpecularLightIntensity(specular);
	lightingManager.updateUniformVariables();

	// InputManager
	InputManager inputManager;
	inputManager.bindInputCallbacks();

	// CameraManager
	Camera camera(&inputManager, &windowManager);
	camera.setCameraSpeed(cameraSpeed);
	camera.setViewPlanes(1.0f, 1000.0f);
	camera.setPosition(cameraPosition);
	camera.setViewAngle(45.0f);

	// RenderManager
	RenderManager renderManager(&shaderManager, &lightingManager, &camera, &windowManager, &sphere);
	renderManager.setRenderOptions(framesPerSecond);
	renderManager.bindDisplayCallbacks();
	
	// Main loop
	glutMainLoop();

	return 0;
}