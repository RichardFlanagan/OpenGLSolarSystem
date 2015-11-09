#include <string>
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Assertion.h"
#include "ShaderManager.h"
#include "ModelLoader.h"
#include "RenderManager.h"
#include "LightingManager.h"
#include "Camera.h"
#include "InputManager.h"


unsigned int windowWidth = 800;
unsigned int windowHeight = 600;
unsigned int windowPosX = 100;
unsigned int windowPosY = 100;
std::string windowTitle = "A00193644 : Solar System";

struct ModelContainer {
public:
	GLuint vertexBufferObject;
	int vertexListSize;
};


/*
	Read in the model and create the vertex buffer object from the resulting vertices list
*/
void createVertexBuffer(ModelContainer *container, std::string pathToModel) {
	ModelLoader loader;
	ASSERTION(!loader.loadModelFromObjFile(pathToModel), "Error loading mesh from obj file.");
	
	std::vector<ModelVertex> verts = loader.getVertices();
	container->vertexListSize = verts.size();

	glGenBuffers(1, &container->vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, container->vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ModelVertex) * container->vertexListSize, &verts[0], GL_STATIC_DRAW);
}


/*
	Create the GLut window
*/
void createWindow(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow(windowTitle.c_str());
}


/*
	Initialize GLew, exiting if there is an error
*/
void initGlew() {
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		std::stringstream ss;
		ss << "Error loading GLEW: " << glewGetErrorString(res);
		ASSERTION(res != GLEW_OK, ss.str());
	}
}

int main(int argc, char** argv) {
	createWindow(argc, argv);
	initGlew();

	ModelContainer sphere;
	createVertexBuffer(&sphere, "assets/sphere.obj");
	
	ShaderManager shaderManager;
	shaderManager.loadShaders();

	LightingManager lightingManager(&shaderManager);
	lightingManager.initializeLighting();

	InputManager inputManager = InputManager();
	inputManager.bindInputCallbacks();

	Camera camera(&inputManager);

	RenderManager renderManager(&shaderManager, &camera, sphere.vertexBufferObject, windowWidth, windowHeight, sphere.vertexListSize, 60);
	renderManager.setRenderOptions();
	renderManager.bindDisplayCallbacks();
	
	glutMainLoop();

	return 0;
}