#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "RenderManager.h"
#include "ModelVertex.h"
#include "ShaderManager.h"
#include <iostream>

RenderManager* RenderManager::renderInstance;

void RenderManager::renderScene() {
	// Create our world space to view space transformation matrix
	glm::mat4 worldToViewTransform = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 10.0f), // The position of your camera, in world space
		glm::vec3(0.0f, 0.0f, 0.0f), // where you want to look at, in world space
		glm::vec3(0.0f, 1.0f, 0.0f)  // Camera up direction (set to 0,-1,0 to look upside-down)
		);

	// Create out projection transform
	glm::mat4 projectionTransform = glm::perspective(45.0f, (float)renderInstance->windowWidth / (float)renderInstance->windowHeight, 1.0f, 100.0f);

	// Update the transforms in the shader program on the GPU
	glUniformMatrix4fv(renderInstance->shaderManager->getWorldToViewTransformLocation(), 1, GL_FALSE, &worldToViewTransform[0][0]);
	glUniformMatrix4fv(renderInstance->shaderManager->getProjectionTransformLocation(), 1, GL_FALSE, &projectionTransform[0][0]);

	glUniform1f(renderInstance->shaderManager->getKaLocation(), 0.8f);
	glUniform1f(renderInstance->shaderManager->getKdLocation(), 0.8f);

	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, renderInstance->vertexBufferObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (const GLvoid*)12);

	static float y = 0.0f;
	//y += 0.01f;
	glm::mat4 trans = glm::mat4(1.0f);

	static float angle = 0.0f;
	angle += 0.01f;
	glm::mat4 rot = glm::mat4(1.0f);

	glm::mat4 modelToWorldTransform = glm::mat4(1.0f);

	for (unsigned int i = 0; i<3; i++) {
		trans = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + (i*3.0f), y, 0.0f));
		rot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
		modelToWorldTransform = trans * rot;
		glUniformMatrix4fv(renderInstance->shaderManager->getModelToWorldTransformLocation(), 1, GL_FALSE, &modelToWorldTransform[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, renderInstance->vertexListSize);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glutSwapBuffers();
}

void RenderManager::initializeGlutCallbacks() {
	glutDisplayFunc(RenderManager::renderScene);
	glutIdleFunc(RenderManager::renderScene);
}