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
	void setDiffuseLightIntensity(glm::vec3 vec);
	void setSpecularLightIntensity(glm::vec3 vec);

	glm::vec3 getAmbientLightIntensity() const;
	glm::vec3 getDiffuseLightIntensity() const;
	glm::vec3 getSpecularLightIntensity() const;

	void setKa(float n);
	void setKd(float n);
	void setKs(float n);

private:
	ShaderManager* shaderManager;

	glm::vec3 ambientLightIntensity;
	glm::vec3 diffuseLightIntensity;
	glm::vec3 specularLightIntensity;

	float ka;
	float kd;
	float ks;
};

#endif // LIGHTING_MANAGER_H