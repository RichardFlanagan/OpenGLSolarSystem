#include "RenderManager.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "ModelVertex.h"
#include "ShaderManager.h"
#include "PlanetaryBody.h"
#include "PlanetManager.h"


/*
	The instance of the RenderManager. This is required for the GLut display callback to reference the instansiated object attributes.
*/
RenderManager* RenderManager::thisInstance;

RenderManager::RenderManager(ShaderManager *sm, Camera *cam, GLuint vbo, int w, int h, int size, int fps) {
	shaderManager = sm;
	camera = cam;
	vertexBufferObject = vbo;
	windowWidth = w;
	windowHeight = h;
	vertexListSize = size;
	framesPerSecond = fps;
	thisInstance = this;
};

void RenderManager::renderSceneCallback() {
	thisInstance->camera->update();

	// Create our world space to view space transformation matrix
	glm::mat4 worldToViewTransform = thisInstance->camera->getWorldToViewMatrix();

	// Create out projection transform
	glm::mat4 projectionTransform = glm::perspective(45.0f, (float)thisInstance->windowWidth / (float)thisInstance->windowHeight, 1.0f, 10000.0f);

	// Update the transforms in the shader program on the GPU
	glUniformMatrix4fv(thisInstance->shaderManager->getWorldToViewTransformLocation(), 1, GL_FALSE, &worldToViewTransform[0][0]);
	glUniformMatrix4fv(thisInstance->shaderManager->getProjectionTransformLocation(), 1, GL_FALSE, &projectionTransform[0][0]);

	glUniform1f(thisInstance->shaderManager->getKaLocation(), 0.8f);
	glUniform1f(thisInstance->shaderManager->getKdLocation(), 0.8f);

	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, thisInstance->vertexBufferObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (const GLvoid*)12);

	static PlanetManager planetManager;
	std::vector<PlanetaryBody*>* planets = planetManager.getPlanetaryBodies();

	for (unsigned int i = 0; i < planets->size(); i++) {
		planets->at(i)->update();

		glUniformMatrix4fv(thisInstance->shaderManager->getModelToWorldTransformLocation(), 1, GL_FALSE, &planets->at(i)->getModelToWorldTransform()[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, thisInstance->vertexListSize);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glutSwapBuffers();
}

/*void RenderManager::renderSceneCallback() {
	thisInstance->camera->update();

	// Create our world space to view space transformation matrix
	glm::mat4 worldToViewTransform = thisInstance->camera->getWorldToViewMatrix();

	// Create out projection transform
	glm::mat4 projectionTransform = glm::perspective(45.0f, (float)thisInstance->windowWidth / (float)thisInstance->windowHeight, 1.0f, 100.0f);

	// Update the transforms in the shader program on the GPU
	glUniformMatrix4fv(thisInstance->shaderManager->getWorldToViewTransformLocation(), 1, GL_FALSE, &worldToViewTransform[0][0]);
	glUniformMatrix4fv(thisInstance->shaderManager->getProjectionTransformLocation(), 1, GL_FALSE, &projectionTransform[0][0]);

	glUniform1f(thisInstance->shaderManager->getKaLocation(), 0.8f);
	glUniform1f(thisInstance->shaderManager->getKdLocation(), 0.8f);

	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, thisInstance->vertexBufferObject);
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
		glUniformMatrix4fv(thisInstance->shaderManager->getModelToWorldTransformLocation(), 1, GL_FALSE, &modelToWorldTransform[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, thisInstance->vertexListSize);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glutSwapBuffers();
}*/




void RenderManager::timedRenderCallback(int fps) {
	RenderManager::renderSceneCallback();
	glutTimerFunc(1000 / fps, RenderManager::timedRenderCallback, fps);
}

void RenderManager::resizeWindowCallback(int width, int height) {
	glViewport(0, 0, width, height);
	std::cout << width << " " << std::endl;
}

void RenderManager::bindDisplayCallbacks() {
	//
	// NOTE
	// display/idle = draw
	// timer = update
	// 

	//glutDisplayFunc(RenderManager::renderSceneCallback);
	//glutIdleFunc(RenderManager::renderSceneCallback);
	glutTimerFunc(1000 / framesPerSecond, RenderManager::timedRenderCallback, framesPerSecond);
	glutReshapeFunc(RenderManager::resizeWindowCallback);
}

void RenderManager::setRenderOptions() {
	// Enable the z-buffer
	glEnable(GL_DEPTH_TEST);
	// GL_LESS - Passes if the incoming depth value is less than the stored depth value
	glDepthFunc(GL_LESS);

	//Enable backface culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	// Set the default screen colour
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}