/*
File: Rendermanager.h
Author: Richard Flanagan
Description:
*/
#ifndef RENDERER_MANAGER_H
#define RENDERER_MANAGER_H
#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ShaderManager.h"
#include "Camera.h"

class RenderManager {
public:
	RenderManager(ShaderManager *sm, Camera *cam, GLuint vbo, int w, int h, int size);
	~RenderManager() {};
	void bindDisplayCallbacks();
private:
	static void renderSceneCallback();
	static RenderManager *thisInstance;

	ShaderManager *shaderManager;
	Camera *camera;
	GLuint vertexBufferObject;
	int windowWidth;
	int windowHeight;
	int vertexListSize;
};

#endif // RENDERER_MANAGER_H