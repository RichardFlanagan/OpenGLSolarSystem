#include "RenderManager.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "ModelVertex.h"
#include "ShaderManager.h"
#include "WindowManager.h"
#include "PlanetaryBody.h"
#include "PlanetManager.h"


/*
	The instance of the RenderManager. This is required for the GLut display callback to reference the instansiated object attributes.
*/
RenderManager* RenderManager::thisInstance;
GLboolean RenderManager::requiresUpdate;

RenderManager::RenderManager(ShaderManager *sm, Camera *cam, WindowManager* window, VBO* vbo) {
	shaderManager = sm;
	camera = cam;
	windowManager = window;
	vertexBufferObject = vbo;

	framesPerSecond = 60;
	requiresUpdate = false;

	thisInstance = this;
};

void RenderManager::renderSceneCallback() {
	if (requiresUpdate) {
		thisInstance->camera->update();
	}

	// Update the camera location
	glUniform3fv(thisInstance->shaderManager->getCameraPositionLocation(), 1, &thisInstance->camera->getPosition()[0]);
	
	// Update the worldToViewTransform in the shader
	glm::mat4 worldToViewTransform = thisInstance->camera->getWorldToViewMatrix();
	glUniformMatrix4fv(thisInstance->shaderManager->getWorldToViewTransformLocation(), 1, GL_FALSE, &worldToViewTransform[0][0]);

	// Update the projectionTransform in the shader
	glm::mat4 projectionTransform = thisInstance->camera->getProjectionMatrix();
	glUniformMatrix4fv(thisInstance->shaderManager->getProjectionTransformLocation(), 1, GL_FALSE, &projectionTransform[0][0]);

	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, thisInstance->vertexBufferObject->getVertexBufferObject());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (const GLvoid*)12);

	static PlanetManager planetManager;
	std::vector<PlanetaryBody*>* planets = planetManager.getPlanetaryBodies();

	for (unsigned int i = 0; i < planets->size(); i++) {
		if (requiresUpdate) {
			planets->at(i)->update();
			//}
			//glm::vec3 pos = -glm::transpose(glm::mat3(planets->at(i)->getModelToWorldTransform())*vec;
			
			if (planets->at(i)->getName() == "aa") {

				glm::mat4 mat = planets->at(i)->getModelToWorldTransform();
				mat = glm::transpose(mat);
				glm::mat3 m3 = glm::mat3(mat);
				glm::vec3 v3 = glm::vec3(mat[2]);

				/*
				std::cout << mat[0].x << " ";
				std::cout << mat[0].y << " ";
				std::cout << mat[0].z << " ";
				std::cout << mat[0].w << std::endl;

				std::cout << mat[1].x << " ";
				std::cout << mat[1].y << " ";
				std::cout << mat[1].z << " ";
				std::cout << mat[1].w << std::endl;

				std::cout << mat[2].x << " ";
				std::cout << mat[2].y << " ";
				std::cout << mat[2].z << " ";
				std::cout << mat[2].w << std::endl;

				std::cout << mat[3].x << " ";
				std::cout << mat[3].y << " ";
				std::cout << mat[3].z << " ";
				std::cout << mat[3].w << std::endl << std::endl;
				*/

				/*
				std::cout << m3[0].x << " ";
				std::cout << m3[0].y << " ";
				std::cout << m3[0].z << std::endl;

				std::cout << m3[1].x << " ";
				std::cout << m3[1].y << " ";
				std::cout << m3[1].z << std::endl;

				std::cout << m3[2].x << " ";
				std::cout << m3[2].y << " ";
				std::cout << m3[2].z << std::endl << std::endl;
				*/

				/*
				std::cout << v3.x << " ";
				std::cout << v3.y << " ";
				std::cout << v3.z << std::endl << std::endl;
				*/

				glm::vec3 tt = glm::transpose(m3) * v3;
				tt = glm::normalize(-tt);
				std::cout << tt.x << " ";
				std::cout << tt.y << " ";
				std::cout << tt.z << std::endl << std::endl;

				glUniform3fv(thisInstance->shaderManager->getDirectionalLightDirectionLocation(), 1, &tt[0]);
			}
		}
		
		//glUniform3fv(thisInstance->shaderManager->getDirectionalLightDirectionLocation(), 1, &(planets->at(i)->getOrbitVector())[0]);

		glUniformMatrix4fv(thisInstance->shaderManager->getModelToWorldTransformLocation(), 1, GL_FALSE, &planets->at(i)->getModelToWorldTransform()[0][0]);
		glUniform3fv(thisInstance->shaderManager->getModelColourLocation(), 1, &planets->at(i)->getColour()[0]);
		glDrawArrays(GL_TRIANGLES, 0, thisInstance->vertexBufferObject->getVertexListSize());
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glutSwapBuffers();
	requiresUpdate = false;
}


void RenderManager::timedRenderCallback(int fps) {
	requiresUpdate = true;
	glutTimerFunc(1000/fps, RenderManager::timedRenderCallback, fps);
}

void RenderManager::bindDisplayCallbacks() {
	glutDisplayFunc(RenderManager::renderSceneCallback);
	glutIdleFunc(RenderManager::renderSceneCallback);
	glutTimerFunc(1000/framesPerSecond, RenderManager::timedRenderCallback, framesPerSecond);
}

void RenderManager::setRenderOptions(GLuint fps) {
	framesPerSecond = fps;

	// Enable the z-buffer
	glEnable(GL_DEPTH_TEST);
	// GL_LESS - Passes if the incoming depth value is less than the stored depth value
	glDepthFunc(GL_LESS);

	//Enable backface culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	// Set the default screen colour
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
}