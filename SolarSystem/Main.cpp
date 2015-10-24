/*#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include <vector>

#include "Assertion.h"
#include "ShaderManager.h"
#include "ModelLoader.h"
#include "RenderManager.h"
#include "LightingManager.h"

unsigned int windowWidth = 800;
unsigned int windowHeight = 600;
unsigned int windowPosX = 100;
unsigned int windowPosY = 100;
std::string windowTitle = "A00193644 : Solar System";
GLuint vertexBufferObject;
int vertexListSize = 0;

void createWindow() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow(windowTitle.c_str());
}

void initGlew() {
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		std::stringstream ss;
		ss << "Error loading GLEW: " << glewGetErrorString(res);
		ASSERTION(res != GLEW_OK, ss.str());
	}
}

void setRenderOptions() {
	// Enable the z-buffer
	glEnable(GL_DEPTH_TEST);
	// GL_LESS - Passes if the incoming depth value is less than the stored depth value
	glDepthFunc(GL_LESS);

	//Enable backface culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void createVertexBuffer(){
	ModelLoader mesh;
	if (!mesh.loadModelFromObjFile("assets/sphere.obj")){
		std::cerr << "Error loading mesh from obj file." << std::endl;
		system("pause");
		exit(0);
	}
	std::vector<ModelVertex> verts = mesh.getVertices();
	vertexListSize = verts.size();

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ModelVertex) * vertexListSize, &verts[0], GL_STATIC_DRAW);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	createWindow(); 
	initGlew();

	createVertexBuffer();
	setRenderOptions();

	ShaderManager shaderManager;
	shaderManager.loadShaders();

	std::cout << shaderManager.getModelToWorldTransformLocation() << std::endl;
	std::cout << shaderManager.getWorldToViewTransformLocation() << std::endl;
	std::cout << shaderManager.getProjectionTransformLocation() << std::endl;
	std::cout << shaderManager.getKaLocation() << std::endl;
	std::cout << shaderManager.getKdLocation() << std::endl;

	RenderManager renderManager(&shaderManager, vertexBufferObject, windowWidth, windowHeight, vertexListSize);
	renderManager.initializeGlutCallbacks();

	LightingManager lightingManager;
	lightingManager.initializeLighting();
    
    glutMainLoop();
    
    return 0;
}*/









#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Assertion.h"
#include "ShaderManager.h"
#include "ModelLoader.h"
#include "RenderManager.h"
#include "LightingManager.h"


using namespace std;
using namespace glm;

unsigned int windowWidth = 800;
unsigned int windowHeight = 600;
unsigned int windowPosX = 100;
unsigned int windowPosY = 100;
std::string windowTitle = "A00193644 : Solar System";
GLuint vertexBufferObject;
int vertexListSize = 0;

ShaderManager shaderManager;

void createVertexBuffer() {
	ModelLoader mesh;
	if (!mesh.loadModelFromObjFile("assets/sphere.obj")) {
		std::cerr << "Error loading mesh from obj file." << std::endl;
		system("pause");
		exit(0);
	}
	std::vector<ModelVertex> verts = mesh.getVertices();
	vertexListSize = verts.size();

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ModelVertex) * vertexListSize, &verts[0], GL_STATIC_DRAW);
}

void createWindow() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow(windowTitle.c_str());
}

void initGlew() {
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		std::stringstream ss;
		ss << "Error loading GLEW: " << glewGetErrorString(res);
		ASSERTION(res != GLEW_OK, ss.str());
	}
}

void setRenderOptions() {
	// Enable the z-buffer
	glEnable(GL_DEPTH_TEST);
	// GL_LESS - Passes if the incoming depth value is less than the stored depth value
	glDepthFunc(GL_LESS);

	//Enable backface culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	createWindow();
	initGlew();
	setRenderOptions();

	createVertexBuffer();
	shaderManager.loadShaders();

	LightingManager lightingManager(&shaderManager);
	lightingManager.initializeLighting();

	RenderManager renderManager(&shaderManager, vertexBufferObject, windowWidth, windowHeight, vertexListSize);
	renderManager.initializeGlutCallbacks();

	glutMainLoop();

	return 0;
}