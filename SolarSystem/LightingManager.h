#ifndef LIGHTING_MANAGER_H
#define LIGHTING_MANAGER_H

#include <GL/freeglut.h>
#include "ShaderManager.h"

class LightingManager {
public:
	LightingManager(ShaderManager *sm) : shaderManager(sm) {};
	~LightingManager() {};
	void initializeLighting();
private:
	ShaderManager* shaderManager;
};

#endif // LIGHTING_MANAGER_H