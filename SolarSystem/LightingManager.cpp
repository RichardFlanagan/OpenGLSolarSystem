#include "LightingManager.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "ShaderManager.h"

LightingManager::LightingManager(ShaderManager *sm) {
	shaderManager = sm;
	ambientLightIntensity = glm::vec3(0.3f, 0.3f, 0.3f);
	directionalLightDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	directionalLightIntensity = glm::vec3(0.5f);
	specularLightIntensity = glm::vec3(1.0f);
	ka = 0.8f;
	kd = 0.8f;
	ks = 0.8f;
}

void LightingManager::updateUniformVariables() {
	// Set up the ambient light
	glUniform3fv(shaderManager->getAmbientLightIntensityLocation(), 1, &ambientLightIntensity[0]);
	glUniform1f(shaderManager->getKaLocation(), ka);

	// Set up the directional light
	glm::normalize(directionalLightDirection);
	glUniform3fv(shaderManager->getDirectionalLightDirectionLocation(), 1, &directionalLightDirection[0]);
	glUniform3fv(shaderManager->getDirectionalLightIntensityLocation(), 1, &directionalLightIntensity[0]);
	glUniform1f(shaderManager->getKdLocation(), kd);

	// Set up the specular light
	glUniform3fv(shaderManager->getSpecularLightIntensityLocation(), 1, &specularLightIntensity[0]);
	glUniform1f(shaderManager->getKsLocation(), ks);
}

void LightingManager::setAmbientLightIntensity(glm::vec3 vec) {
	ambientLightIntensity = vec;
}
void LightingManager::setDirectionalLightDirection(glm::vec3 vec) {
	directionalLightDirection = vec;
}
void LightingManager::setDirectionalLightIntensity(glm::vec3 vec) {
	directionalLightIntensity = vec;
}
void LightingManager::setSpecularLightIntensity(glm::vec3 vec) {
	specularLightIntensity = vec;
}

void LightingManager::setKa(float n) {
	ka = n;
}
void LightingManager::setKd(float n) {
	kd = n;
}
void LightingManager::setKs(float n) {
	ks = n;
}