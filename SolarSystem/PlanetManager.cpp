#include "PlanetManager.h"
#include <glm/glm.hpp>
#include "PlanetaryBody.h"

PlanetManager::PlanetManager() {
	globalScale = 0.3f;
	globalRotateSpeed = 1.0f;
	globalOrbitSpeed = 1.0f;
	globalDistScale = 10.0f;

	createSol();
	createMercury();
	createVenus();
	createEarth();
	createLuna();
	createMars();
	createJupiter();
	createSaturn();
	createUranus();
	createNeptune();

	populatePlanetList();
}


std::vector<PlanetaryBody*>* PlanetManager::getPlanetaryBodies() {
	return &planetaryBodies;
}


void PlanetManager::populatePlanetList() {
	planetaryBodies.push_back(&sol);
	planetaryBodies.push_back(&mercury);
	planetaryBodies.push_back(&venus);
	planetaryBodies.push_back(&earth);
	planetaryBodies.push_back(&luna);
	planetaryBodies.push_back(&mars);
	planetaryBodies.push_back(&jupiter);
	planetaryBodies.push_back(&saturn);
	planetaryBodies.push_back(&uranus);
	planetaryBodies.push_back(&neptune);
}


void PlanetManager::createSol() {
	sol.setName("Sol");
	sol.setScale(glm::vec3(globalScale*10.9f));
	sol.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed/25.05f); // 25.05 days
	sol.setOrbitDistance(glm::vec3(0.0f));
}


void PlanetManager::createMercury() {
	// note, eliptical orbit
	mercury.setName("Mercury");
	mercury.setParent(&sol);
	mercury.setScale(glm::vec3(globalScale*0.3829f)); // 0.3829 earths
	mercury.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed/58.6f);
	mercury.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 2.04f);
	mercury.setOrbitDistance(glm::vec3(globalDistScale * 0.387f, 0.0f, 0.0f)); // 0.387 earth-sun distance
	mercury.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed*4.17f); // 0.24 earth years
	//mercury.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 3.38f);
}


void PlanetManager::createVenus() {
	venus.setName("Venus");
	venus.setParent(&sol);
	venus.setScale(glm::vec3(globalScale*0.95f)); // 0.95 earths
	venus.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*0.004f); 
	venus.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 2.64f);
	venus.setOrbitDistance(glm::vec3(globalDistScale * 0.72f, 0.0f, 0.0f)); // 0.72 earth-sun distance
	venus.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed*1.626f); // 0.615 earth years
	//venus.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 3.86f);
}


void PlanetManager::createEarth() {
	earth.setName("Earth");
	earth.setParent(&sol);
	earth.setScale(glm::vec3(globalScale*1.0f)); // 1 earth
	earth.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*1.0f);
	earth.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), -23.44f);
	earth.setOrbitDistance(glm::vec3(globalDistScale * 1.0f, 0.0f, 0.0f)); // 1 earth-sun distance
	earth.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed*1.0f); // 1 year
	//earth.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 7.155f);
}


void PlanetManager::createLuna() {
	luna.setName("Luna");
	luna.setParent(&earth);
	luna.setScale(glm::vec3(globalScale*0.273f)); // 0.273 earths
	luna.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*27.3f);
	luna.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 6.68f);
	luna.setOrbitDistance(glm::vec3(globalDistScale * 0.15f, 0.0f, 0.0f)); // 0.0026 earth-sun distance (0.15 to see it)
	luna.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 12.0f); // 12 months = 1 year
	luna.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 5.14f);
}

void PlanetManager::createMars() {
	mars.setName("Mars");
	mars.setParent(&sol);
	mars.setScale(glm::vec3(globalScale*0.53f)); // 0.53 earth
	mars.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed/1.02f);
	mars.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 25.19f);
	mars.setOrbitDistance(glm::vec3(globalDistScale * 1.52f, 0.0f, 0.0f)); // 1.52 earth-sun distance
	mars.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), 0.532f); // 1.88 earth years
	//mars.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 5.65f);
}

void PlanetManager::createJupiter() {
	jupiter.setName("Jupiter");
	jupiter.setParent(&sol);
	jupiter.setScale(glm::vec3(globalScale*11.2f)); // 11.2 earth
	jupiter.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*2.4f);
	jupiter.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 3.13f);
	jupiter.setOrbitDistance(glm::vec3(globalDistScale * 5.2f, 0.0f, 0.0f)); // 5.2 earth-sun distance
	jupiter.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), 0.08f); // 11.86 earth years
	//jupiter.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 6.0f);
}

void PlanetManager::createSaturn() {
	saturn.setName("Saturn");
	saturn.setParent(&sol);
	saturn.setScale(glm::vec3(globalScale*9.45f)); // 9.45 earth
	saturn.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*2.2f);
	saturn.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 26.73f);
	saturn.setOrbitDistance(glm::vec3(globalDistScale * 9.58f, 0.0f, 0.0f)); // 9.58 earth-sun distance
	saturn.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), 0.034f); // 29.45 earth years
	//saturn.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 5.51f);
}

void PlanetManager::createUranus() {
	uranus.setName("Uranus");
	uranus.setParent(&sol);
	uranus.setScale(glm::vec3(globalScale*4.0f)); // 4 earth
	uranus.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*1.39f);
	uranus.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 97.7f);
	uranus.setOrbitDistance(glm::vec3(globalDistScale * 19.189f, 0.0f, 0.0f)); // 19.189 earth-sun distance
	uranus.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), 0.0119f); // 84 earth years
	//uranus.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 5.51f);
}

void PlanetManager::createNeptune() {
	neptune.setName("Neptune");
	neptune.setParent(&sol);
	neptune.setScale(glm::vec3(globalScale*3.88f)); // 3.88 earth
	neptune.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*1.49f); 
	neptune.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 28.32f);
	neptune.setOrbitDistance(glm::vec3(globalDistScale * 30.07f, 0.0f, 0.0f)); // 30.07 earth-sun distance
	neptune.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), 0.0061f); // 164.8 earth years
	//neptune.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 6.43f);
}
