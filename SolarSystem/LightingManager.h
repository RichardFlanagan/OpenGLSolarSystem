/*
File: LightingManager.h
Author: Richard Flanagan
Description:
*/
#ifndef LIGHTING_MANAGER_H
#define LIGHTING_MANAGER_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ShaderManager.h"

class LightingManager {
public:
	LightingManager(ShaderManager *sm);
	~LightingManager() {};
	void initializeLighting();
private:
	ShaderManager* shaderManager;
};

#endif // LIGHTING_MANAGER_H