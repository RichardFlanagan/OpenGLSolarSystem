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
#include "WindowManager.h"
#include "VBO.h"

class RenderManager {
public:
	RenderManager(ShaderManager *sm, Camera *cam, WindowManager* window, VBO* vbo);
	~RenderManager() {};

	void bindDisplayCallbacks();
	void setRenderOptions(GLuint fps);
private:
	static void renderSceneCallback();
	static void timedRenderCallback(int fps);
	//static void RenderManager::resizeWindowCallback(int width, int height);
	static RenderManager *thisInstance;
	static GLboolean requiresUpdate;

	ShaderManager *shaderManager;
	Camera *camera;
	WindowManager* windowManager;
	VBO* vertexBufferObject;
	
	GLuint framesPerSecond;
};

#endif // RENDERER_MANAGER_H