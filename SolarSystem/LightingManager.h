/*
File: LightingManager.h
Author: Richard Flanagan
Description:
*/
#ifndef LIGHTING_MANAGER_H
#define LIGHTING_MANAGER_H

#include "ShaderManager.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class LightingManager {
public:
	LightingManager(ShaderManager *sm);
	~LightingManager() {};

	void updateUniformVariables();
	void setAmbientLightIntensity(glm::vec3 vec);
	void setDirectionalLightDirection(glm::vec3 vec);
	void setDirectionalLightIntensity(glm::vec3 vec);

private:
	ShaderManager* shaderManager;

	glm::vec3 ambientLightIntensity;
	glm::vec3 directionalLightDirection;
	glm::vec3 directionalLightIntensity;
};

#endif // LIGHTING_MANAGER_H