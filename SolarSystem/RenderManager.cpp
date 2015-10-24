#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "RenderManager.h"
#include "ModelVertex.h"
#include "ShaderManager.h"
#include <iostream>

/*
	The instance of the RenderManager. This is required for the GLut display callback to reference the instansiated object attributes.
*/
RenderManager* RenderManager::renderInstance;

void RenderManager::renderSceneCallback() {
	// Create our world space to view space transformation matrix
	glm::mat4 worldToViewTransform = renderInstance->camera->getWorldToViewMatrix();

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

void RenderManager::bindDisplayCallbacks() {
	glutDisplayFunc(RenderManager::renderSceneCallback);
	glutIdleFunc(RenderManager::renderSceneCallback);
}