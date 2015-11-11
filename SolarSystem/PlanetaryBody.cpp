#include "PlanetaryBody.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>


PlanetaryBody::PlanetaryBody() {
	name = "PlanetaryBody";
	parent = nullptr;

	// Scale
	scaleVector = glm::vec3(1.0f); // Original size

	// Rotation (day)
	rotationVector = glm::vec3(0.0f, 1.0f, 0.0f); // 0 degrees on y-axis
	rotationDelta = 0.0f;
	currentRotationAngle = 0.0f;

	// Angle from y-plane
	planetTiltVector = glm::vec3(0.0f, 0.0f, 1.0f); // 0 degrees on z-axis
	planetTiltAngle = 0.0f;

	// Distance from the point of orbit
	orbitDistanceVector = glm::vec3(0.0f); // At origin

	// Orbit plane about parent
	orbitVector = glm::vec3(0.0f, 1.0f, 0.0f); // 0 degrees on y-axis;
	orbitDelta = 0.0f;
	currentOrbitAngle = 0.0f;

	// Angle of orbit about parent
	orbitTiltVector = glm::vec3(0.0f, 0.0f, 1.0f); // 0 degrees on z-axis;
	orbitTiltAngle = 0.0f;

	// Model to world transform
	modelToWorldTransform = glm::mat4(1.0f);
}

void PlanetaryBody::update() {

	// Scale against Sol
	scaleMatrix = glm::scale(glm::mat4(1.0f), scaleVector);

	// Rotation (day)
	currentRotationAngle += rotationDelta;
	rotationMatrix = glm::rotate(glm::mat4(1.0f), currentRotationAngle, rotationVector);

	// Angle from y-plane
	planetTiltMatrix = glm::rotate(glm::mat4(1.0f), planetTiltAngle, planetTiltVector);

	// Distance from the point of orbit
	orbitDistanceMatrix = glm::translate(glm::mat4(1.0f), orbitDistanceVector);

	// Orbit plane about parent
	currentOrbitAngle += orbitDelta;
	orbitMatrix = glm::rotate(glm::mat4(1.0f), currentOrbitAngle, orbitVector);

	// Angle of orbit about parent
	orbitTiltMatrix = glm::rotate(glm::mat4(1.0f), orbitTiltAngle, orbitTiltVector);

	// Model to world transform
	modelToWorldTransform = (orbitTiltMatrix * orbitMatrix * orbitDistanceMatrix * planetTiltMatrix * rotationMatrix * scaleMatrix);

	if (parent) {
		// Parent translation and rotation
		glm::mat4 parentOrbitDistance = parent->getOrbitDistanceMatrix();
		glm::mat4 parentOrbit = parent->getOrbitMatrix();

		// Model to world transform to parent
		modelToWorldTransform = parentOrbit * parentOrbitDistance * modelToWorldTransform;
	}
}



std::string PlanetaryBody::getName() const {
	return name; 
}
void PlanetaryBody::setName(std::string newName) { 
	name = newName; 
}

PlanetaryBody* PlanetaryBody::getParent() const {
	return parent; 
}
void PlanetaryBody::setParent(PlanetaryBody* newParent) { 
	parent = newParent; 
}

void PlanetaryBody::setScale(glm::vec3 newScaleVector) {
	scaleVector = newScaleVector;
}
glm::vec3 PlanetaryBody::getScaleVector() const {
	return scaleVector;
}
glm::mat4 PlanetaryBody::getScaleMatrix() const {
	return scaleMatrix;
}

void PlanetaryBody::setRotation(glm::vec3 newRotationVector, float newRotationDelta) {
	rotationVector = newRotationVector;
	rotationDelta = newRotationDelta;
}
glm::vec3 PlanetaryBody::getRotationVector() const {
	return rotationVector;
}
float PlanetaryBody::getRotationDelta() const {
	return rotationDelta;
}
glm::mat4 PlanetaryBody::getRotationMatrix() const {
	return rotationMatrix;
}

void PlanetaryBody::setPlanetTilt(glm::vec3 newPlanetTiltVector, float newPlanetTiltDelta) {
	planetTiltVector = newPlanetTiltVector;
	planetTiltAngle = newPlanetTiltDelta;
}
glm::vec3 PlanetaryBody::getPlanetTiltVector() const {
	return planetTiltVector;
}
float PlanetaryBody::getPlanetTiltAngle() const {
	return planetTiltAngle;
}
glm::mat4 PlanetaryBody::getPlanetTiltMatrix() const {
	return planetTiltMatrix;
}

void PlanetaryBody::setOrbitDistance(glm::vec3 newOrbitDistanceVector) {
	orbitDistanceVector = newOrbitDistanceVector;
}
glm::vec3 PlanetaryBody::getOrbitDistanceVector() const {
	return orbitDistanceVector;
}
glm::mat4 PlanetaryBody::getOrbitDistanceMatrix() const {
	return orbitDistanceMatrix;
}

void PlanetaryBody::setOrbit(glm::vec3 newOrbitVector, float newOrbitDelta) {
	orbitVector = newOrbitVector;
	orbitDelta = newOrbitDelta;
}
glm::vec3 PlanetaryBody::getOrbitVector() const {
	return orbitVector;
}
float PlanetaryBody::getOrbitDelta() const {
	return orbitDelta;
}
glm::mat4 PlanetaryBody::getOrbitMatrix() const {
	return orbitMatrix;
}

void PlanetaryBody::setOrbitTilt(glm::vec3 newOrbitTiltVector, float newOrbitTiltDelta) {
	orbitTiltVector = newOrbitTiltVector;
	orbitTiltAngle = newOrbitTiltDelta;
}
glm::vec3 PlanetaryBody::getOrbitTiltVector() const {
	return orbitTiltVector;
}
float PlanetaryBody::getOrbitTiltAngle() const {
	return orbitTiltAngle;
}
glm::mat4 PlanetaryBody::getOrbitTiltMatrix() const {
	return orbitTiltMatrix;
}

glm::mat4 PlanetaryBody::getModelToWorldTransform() const {
	return modelToWorldTransform;
}
