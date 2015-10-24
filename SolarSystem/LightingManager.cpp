#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "LightingManager.h"

void LightingManager::initializeLighting() {
	// Setup the ambient light
	glm::vec3 ambientLightIntensity = glm::vec3(0.2f, 0.2f, 0.2f);
	glUniform3fv(shaderManager->getAmbientLightIntensityLocation(), 1, &ambientLightIntensity[0]);

	// Setup the direactional light
	glm::vec3 directionalLightDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::normalize(directionalLightDirection);
	glUniform3fv(shaderManager->getDirectionalLightDirectionLocation(), 1, &directionalLightDirection[0]);
	glm::vec3 directionalLightIntensity = glm::vec3(0.7f, 0.7f, 0.7f);
	glUniform3fv(shaderManager->getDirectionalLightIntensityLocation(), 1, &directionalLightIntensity[0]);
}