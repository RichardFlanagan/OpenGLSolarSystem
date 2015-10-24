#ifndef LIGHTING_MANAGER_H
#define LIGHTING_MANAGER_H

#include <GL/freeglut.h>
#include "ShaderManager.h"

class LightingManager {
public:
	LightingManager(ShaderManager *sm) : shaderManager(sm) {};
	~LightingManager() {};
	void initializeLighting();
	/*const GLuint getAmbientLightIntensityLocation();
	const GLuint getDirectionalLightDirectionLocation();
	const GLuint getDirectionalLightIntensityLocation();*/
private:
	/*GLuint gAmbientLightIntensityLocation;
	GLuint gDirectionalLightDirectionLocation;
	GLuint gDirectionalLightIntensityLocation;*/
	ShaderManager* shaderManager;
};

#endif // LIGHTING_MANAGER_H