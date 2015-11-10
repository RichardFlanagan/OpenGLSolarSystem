#include "RenderManager.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "ModelVertex.h"
#include "ShaderManager.h"


struct PlanetaryBody {
	PlanetaryBody* parent;
	std::string name = "PlanetaryBody";

	glm::vec3 scaleVec;
	glm::vec3 rotationVec;
	float rotationSpeed = 0.0f;
	glm::vec3 planetTiltVec;
	glm::vec3 orbitDistanceVec;
	glm::vec3 orbitVec;
	float orbitSpeed = 0.0f;
	glm::vec3 orbitTiltVec;
	
	glm::mat4 scale;
	glm::mat4 rotation;
	glm::mat4 planetTilt;
	glm::mat4 orbitDistance;
	glm::mat4 orbit;
	glm::mat4 orbitTilt;
	glm::mat4 modelToWorldTransform = glm::mat4(0.0f);
	

	PlanetaryBody() {};

	PlanetaryBody(
		glm::vec3 scaleVec,
		glm::vec3 orbitVec,
		float orbitSpeed,
		glm::vec3 orbitDistanceVec,
		std::string name,
		float rotationSpeed) :
		scaleVec(scaleVec), orbitVec(orbitVec), orbitSpeed(orbitSpeed), orbitDistanceVec(orbitDistanceVec), name(name), rotationSpeed(rotationSpeed) {}

	PlanetaryBody(std::string name, PlanetaryBody* parent, glm::vec3 scaleVec, glm::vec3 rotationVec, float rotationSpeed, glm::vec3 planetTiltVec, glm::vec3 orbitDistanceVec, glm::vec3 orbitVec, float orbitSpeed, glm::vec3 orbitTiltVec) :
		name(name), parent(parent), scaleVec(scaleVec), rotationVec(rotationVec), rotationSpeed(rotationSpeed), planetTiltVec(planetTiltVec), 
		orbitDistanceVec(orbitDistanceVec), orbitVec(orbitVec), orbitSpeed(orbitSpeed), orbitTiltVec(orbitTiltVec) {}


	PlanetaryBody(std::string name, PlanetaryBody* parent, glm::vec3 scaleVec, float rotationSpeed, glm::vec3 orbitDistanceVec, glm::vec3 orbitVec, float orbitSpeed) :
		name(name), parent(parent), scaleVec(scaleVec), rotationSpeed(rotationSpeed), orbitDistanceVec(orbitDistanceVec), orbitVec(orbitVec), orbitSpeed(orbitSpeed) {}


	void update() {

		if (name == "Sol") {
			// Scale against Sol
			scale = glm::scale(glm::mat4(1.0f), scaleVec);

			// Rotation (day)
			static float angleOfRotation = 0.0f; 
			angleOfRotation += rotationSpeed;
			rotation = glm::rotate(glm::mat4(1.0f), angleOfRotation, glm::vec3(0.0f, 1.0f, 0.0f));
			
			// Distance from the point of orbit
			orbitDistance = glm::translate(glm::mat4(1.0f), orbitDistanceVec);

			modelToWorldTransform = orbitDistance * rotation * scale;
		} 
		else if (name == "Earth") {
			// Scale against Sol
			scale = glm::scale(glm::mat4(1.0f), scaleVec);

			// Rotation (day)
			static float angleOfRotation = 0.0f; 
			angleOfRotation += rotationSpeed;
			rotation = glm::rotate(glm::mat4(1.0f), angleOfRotation, glm::vec3(0.0f, 1.0f, 0.0f));

			// Angle from y-plane
			planetTilt = glm::rotate(glm::mat4(1.0f), glm::radians(-23.44f), glm::vec3(0.0f, 0.0f, 1.0f));
			
			// Distance from the point of orbit
			static float orbitAngle = 0.0f;
			orbitAngle += orbitSpeed;
			orbitDistance = glm::translate(glm::mat4(1.0f), orbitDistanceVec);
			
			// Orbit plane about parent
			orbit = glm::rotate(glm::mat4(1.0f), orbitAngle, glm::vec3(0.0f, 1.0f, 0.0f));

			// Angle above x-plane
			orbitTilt = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

			//glm::mat4 parentOrbitDistance = glm::translate(glm::mat4(1.0f), parent->translateVec);
			//glm::mat4 parentOrbit = glm::rotate(glm::mat4(1.0f), parent->angle, parent->rotateVec);
			modelToWorldTransform = (orbit * orbitDistance * planetTilt * rotation * scale);
		}
		else if (name == "Luna") {
			// Scale against Sol
			scale = glm::scale(glm::mat4(1.0f), scaleVec);

			// Rotation (day)
			static float angleOfRotation = 0.0f; 
			angleOfRotation += rotationSpeed;
			rotation = glm::rotate(glm::mat4(1.0f), angleOfRotation, glm::vec3(0.0f, 1.0f, 0.0f));

			// Angle from y-plane
			planetTilt = glm::rotate(glm::mat4(1.0f), glm::radians(6.68f), glm::vec3(0.0f, 0.0f, 1.0f));

			// Distance from the point of orbit
			orbitDistance = glm::translate(glm::mat4(1.0f), orbitDistanceVec);

			// Orbit plane about parent
			static float orbitAngle = 0.0f;
			orbitAngle += orbitSpeed;
			orbit = glm::rotate(glm::mat4(1.0f), orbitAngle, glm::vec3(0.0f, 1.0f, 0.0f));

			// Angle above x-plane
			orbitTilt = glm::rotate(glm::mat4(1.0f), glm::radians(15.14f), glm::vec3(0.0f, 0.0f, 1.0f));

			// Parent translation and rotation
			glm::mat4 parentOrbitDistance = parent->orbitDistance;
			glm::mat4 parentOrbit = parent->orbit;

			// Model to world transform
			modelToWorldTransform = parentOrbit * parentOrbitDistance * (orbitTilt * orbit * orbitDistance * planetTilt * rotation * scale);
		}

	}

};

struct Planet : public PlanetaryBody {

};



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

	static const int planetListLength = 3;
	static PlanetaryBody planets[planetListLength]{
		PlanetaryBody(
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f), 0.01f,
			glm::vec3(0.0f, 0.0f, 0.0f),
			"Sol", 0.01f),
		PlanetaryBody(
			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(0.0f, 1.0f, 0.0f), 0.01f,
			glm::vec3(3.0f, 0.0f, 0.0f),
			"Earth", 0.1f),
		PlanetaryBody(
			glm::vec3(0.2f, 0.2f, 0.2f),
			glm::vec3(0.0f, 1.0f, 0.0f), 0.01f,
			glm::vec3(1.0f, 0.0f, 0.0f),
			"Luna", 0.1f)
	};
	planets[1].parent = &planets[0];
	planets[2].parent = &planets[1];


	//static const int planetListLength = 3;

	//PlanetaryBody sol("Sol", nullptr, glm::vec3(1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.01f,
	//	glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0.0f));

	//PlanetaryBody earth("Earth", &sol, glm::vec3(0.5f), glm::vec3(0.0f, 1.0f, 0.0f), 0.01f,
	//	glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0.0f));

	//PlanetaryBody sol("Sol", nullptr,  glm::vec3(1.0f), 0.1f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.01f);
	//PlanetaryBody earth("Earth", &sol, glm::vec3(0.5f), 0.1f, glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.01f);
	//PlanetaryBody luna("Luna", &earth, glm::vec3(0.2f), 0.1f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.01f);

	//static const int planetListLength = 3;
	//static PlanetaryBody planets[planetListLength]{sol, earth, luna};




	for (int i = 0; i < planetListLength; i++) {
		planets[i].update();

		glUniformMatrix4fv(thisInstance->shaderManager->getModelToWorldTransformLocation(), 1, GL_FALSE, &planets[i].modelToWorldTransform[0][0]);
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