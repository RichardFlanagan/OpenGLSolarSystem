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
	RenderManager(ShaderManager *sm, Camera *cam, GLuint vbo, int w, int h, int size, int fps);
	~RenderManager() {};
	void bindDisplayCallbacks();
	void setRenderOptions();
private:
	static void renderSceneCallback();
	static void timedRenderCallback(int fps);
	static void RenderManager::resizeWindowCallback(int width, int height);
	static RenderManager *thisInstance;

	ShaderManager *shaderManager;
	Camera *camera;
	GLuint vertexBufferObject;
	int windowWidth;
	int windowHeight;
	int vertexListSize;
	int framesPerSecond;
	static bool draw;
};

#endif // RENDERER_MANAGER_H