#ifndef RENDERER_MANAGER_H
#define RENDERER_MANAGER_H

#include <GL/freeglut.h>
#include "ShaderManager.h"

class RenderManager {
public:
	RenderManager(ShaderManager *sm, GLuint vbo, int w, int h, int size) {
		shaderManager = sm;
		vertexBufferObject = vbo;
		windowWidth = w;
		windowHeight = h;
		vertexListSize = size;
		renderInstance = this;
	};
	~RenderManager() {};
	void initializeGlutCallbacks();
private:
	static void renderScene();
	static RenderManager *renderInstance;

	ShaderManager *shaderManager;
	GLuint vertexBufferObject;
	int windowWidth;
	int windowHeight;
	int vertexListSize;
};

#endif // RENDERER_MANAGER_H