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
#include "LightingManager.h"
#include "Camera.h"
#include "WindowManager.h"
#include "VBO.h"

class RenderManager {
public:
	RenderManager(ShaderManager* sm, LightingManager* lm, Camera* cam, WindowManager* window, VBO* vbo);
	~RenderManager() {};

	void bindDisplayCallbacks();
	void setRenderOptions(GLuint fps);
private:
	static void renderSceneCallback();
	static void timedRenderCallback(int fps);
	static RenderManager *thisInstance;
	static GLboolean requiresUpdate;

	ShaderManager* shaderManager;
	LightingManager* lightingManager;
	Camera* camera;
	WindowManager* windowManager;
	VBO* vertexBufferObject;
	
	GLuint framesPerSecond;
};

#endif // RENDERER_MANAGER_H