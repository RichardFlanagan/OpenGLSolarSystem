#include "LightingManager.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "ShaderManager.h"

LightingManager::LightingManager(ShaderManager *sm) {
	shaderManager = sm;
	ambientLightIntensity = glm::vec3(0.3f, 0.3f, 0.3f);
	directionalLightDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	directionalLightIntensity = glm::vec3(0.0f, 0.0f, 0.0f);
}

void LightingManager::updateUniformVariables() {
	// Setup the ambient light
	glUniform3fv(shaderManager->getAmbientLightIntensityLocation(), 1, &ambientLightIntensity[0]);

	// Setup the direactional light
	glm::normalize(directionalLightDirection);
	glUniform3fv(shaderManager->getDirectionalLightDirectionLocation(), 1, &directionalLightDirection[0]);
	glUniform3fv(shaderManager->getDirectionalLightIntensityLocation(), 1, &directionalLightIntensity[0]);
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