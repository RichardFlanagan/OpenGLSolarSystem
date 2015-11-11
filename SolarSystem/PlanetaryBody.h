#ifndef PLANETARY_BODY_H
#define PLANETARY_BODY_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

class PlanetaryBody {
public:
	PlanetaryBody();
	void update();

	std::string getName() const;
	void setName(std::string name); 
	
	PlanetaryBody* getParent() const;
	void setParent(PlanetaryBody* parent);

	void setScale(glm::vec3 scaleVector);
	glm::vec3 getScaleVector() const;
	glm::mat4 getScaleMatrix() const;

	void setRotation(glm::vec3 rotationVector, float rotationDelta);
	glm::vec3 getRotationVector() const;
	float getRotationDelta() const;
	glm::mat4 getRotationMatrix() const;

	void setPlanetTilt(glm::vec3 planetTiltVector, float planetTiltDelta);
	glm::vec3 getPlanetTiltVector() const;
	float getPlanetTiltAngle() const;
	glm::mat4 getPlanetTiltMatrix() const;

	void setOrbitDistance(glm::vec3 orbitDistanceVector);
	glm::vec3 getOrbitDistanceVector() const;
	glm::mat4 getOrbitDistanceMatrix() const;

	void setOrbit(glm::vec3 orbitVector, float orbitDelta);
	glm::vec3 getOrbitVector() const;
	float getOrbitDelta() const;
	glm::mat4 getOrbitMatrix() const;

	void setOrbitTilt(glm::vec3 orbitTiltVector, float orbitTiltDelta);
	glm::vec3 getOrbitTiltVector() const;
	float getOrbitTiltAngle() const;
	glm::mat4 getOrbitTiltMatrix() const;

	glm::mat4 getModelToWorldTransform() const;

private:
	// Body name
	std::string name;

	// The body which this orbits
	PlanetaryBody* parent;
	

	// Scale
	glm::vec3 scaleVector;
	glm::mat4 scaleMatrix;
	
	// Rotation (day)
	glm::vec3 rotationVector;
	float rotationDelta;
	float currentRotationAngle;
	glm::mat4 rotationMatrix;

	// Angle from y-plane
	glm::vec3 planetTiltVector;
	float planetTiltAngle;
	glm::mat4 planetTiltMatrix;

	// Distance from the point of orbit
	glm::vec3 orbitDistanceVector;
	glm::mat4 orbitDistanceMatrix;

	// Orbit plane about parent
	glm::vec3 orbitVector;
	float orbitDelta;
	float currentOrbitAngle;
	glm::mat4 orbitMatrix;

	// Angle of orbit about parent
	glm::vec3 orbitTiltVector;
	float orbitTiltAngle;
	glm::mat4 orbitTiltMatrix;

	// Model to world transform
	glm::mat4 modelToWorldTransform;
};

#endif // PLANETARY_BODY_H