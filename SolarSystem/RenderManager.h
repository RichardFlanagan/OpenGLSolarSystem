#ifndef RENDERER_MANAGER_H
#define RENDERER_MANAGER_H

#include <GL/freeglut.h>
#include "ShaderManager.h"
#include "Camera.h"

class RenderManager {
public:
	RenderManager(ShaderManager *sm, Camera *cam, GLuint vbo, int w, int h, int size) {
		shaderManager = sm;
		camera = cam;
		vertexBufferObject = vbo;
		windowWidth = w;
		windowHeight = h;
		vertexListSize = size;
		renderInstance = this;
	};
	~RenderManager() {};
	void bindDisplayCallbacks();
private:
	static void renderSceneCallback();
	static RenderManager *renderInstance;

	ShaderManager *shaderManager;
	Camera *camera;
	GLuint vertexBufferObject;
	int windowWidth;
	int windowHeight;
	int vertexListSize;
};

#endif // RENDERER_MANAGER_H