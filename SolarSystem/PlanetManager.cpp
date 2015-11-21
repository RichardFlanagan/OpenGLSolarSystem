#include "PlanetManager.h"
#include <glm/glm.hpp>
#include "PlanetaryBody.h"

PlanetManager::PlanetManager() {
	globalScale = 0.8f;
	globalRotateSpeed = 6.0f;
	globalOrbitSpeed = 1.0f;
	globalDistScale = 20.0f;

	createSol();

	createMercury();

	createVenus();

	createEarth();
	createLuna();

	createMars();
	createDeimos();
	createPhobos();

	createJupiter();
	createGanymede();
	createCallisto();

	createSaturn();
	createRingOfSaturn();
	createTitan();
	createRhea();

	createUranus();
	createTitania();
	createOberon();

	createNeptune();
	createTriton();
	createProteus();

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
	planetaryBodies.push_back(&deimos);
	planetaryBodies.push_back(&phobos);

	planetaryBodies.push_back(&jupiter);
	planetaryBodies.push_back(&ganymede);
	planetaryBodies.push_back(&callisto);

	planetaryBodies.push_back(&saturn);
	planetaryBodies.push_back(&ringOfSaturn);
	planetaryBodies.push_back(&titan);
	planetaryBodies.push_back(&rhea);

	planetaryBodies.push_back(&uranus);
	planetaryBodies.push_back(&titania);
	planetaryBodies.push_back(&proteus);

	planetaryBodies.push_back(&neptune);
	planetaryBodies.push_back(&triton);
	planetaryBodies.push_back(&proteus);
}


void PlanetManager::createSol() {
	sol.setName("Sol");
	//sol.setScale(glm::vec3(globalScale*10.9f));
	sol.setScale(glm::vec3(5.0f));
	sol.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed/25.05f); // 25.05 days
	sol.setOrbitDistance(glm::vec3(0.0f));
	sol.setColour(glm::vec3(1.0f, 1.0f, 0.0f));
}


void PlanetManager::createMercury() {
	mercury.setName("Mercury");
	mercury.setParent(&sol);
	mercury.setScale(glm::vec3(globalScale*0.3829f)); // 0.3829 earths
	mercury.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed/58.6f);
	mercury.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 2.04f);
	mercury.setOrbitDistance(glm::vec3(globalDistScale * 0.387f, 0.0f, 0.0f)); // 0.387 earth-sun distance
	mercury.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed*4.17f); // 0.24 earth years
	mercury.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 3.38f);
	mercury.setColour(glm::vec3(0.8f, 0.8f, 0.8f));
}


void PlanetManager::createVenus() {
	venus.setName("Venus");
	venus.setParent(&sol);
	venus.setScale(glm::vec3(globalScale*0.95f)); // 0.95 earths
	venus.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*0.004f); 
	venus.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 2.64f);
	venus.setOrbitDistance(glm::vec3(globalDistScale * 0.72f, 0.0f, 0.0f)); // 0.72 earth-sun distance
	venus.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed*1.626f); // 0.615 earth years
	venus.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 3.86f);
	venus.setColour(glm::vec3(0.8f, 0.8f, 0.0f));
}


void PlanetManager::createEarth() {
	earth.setName("Earth");
	earth.setParent(&sol);
	earth.setScale(glm::vec3(globalScale*1.0f)); // 1 earth
	earth.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*1.0f);
	earth.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), -23.44f);
	earth.setOrbitDistance(glm::vec3(globalDistScale * 1.0f, 0.0f, 0.0f)); // 1 earth-sun distance
	earth.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed*1.0f); // 1 year
	earth.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 7.155f);
	earth.setColour(glm::vec3(0.0f, 0.5f, 0.5f));
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
	luna.setColour(glm::vec3(0.8f, 0.8f, 0.8f));
}

void PlanetManager::createMars() {
	mars.setName("Mars");
	mars.setParent(&sol);
	mars.setScale(glm::vec3(globalScale*0.53f)); // 0.53 earth
	mars.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed/1.02f);
	mars.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 25.19f);
	mars.setOrbitDistance(glm::vec3(globalDistScale * 1.52f, 0.0f, 0.0f)); // 1.52 earth-sun distance
	mars.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), 0.532f); // 1.88 earth years
	mars.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 5.65f);
	mars.setColour(glm::vec3(0.8f, 0.4f, 0.0f));
}

void PlanetManager::createDeimos() {
	deimos.setName("Deimos");
	deimos.setParent(&mars);
	deimos.setScale(glm::vec3(globalScale*0.1f)); // 0.00178 earth (rounded up to 0.15)
	deimos.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed * 27.3f * 5); // moon*22, rounded to moon*5
	deimos.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
	deimos.setOrbitDistance(glm::vec3(globalDistScale * 0.15f, 0.0f, 0.0f)); // tiny 23k km (0.15 earth-sun to see it)
	deimos.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 12.0f); // tiny 1.26 days (rounded up to 1x moon)
	deimos.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.93f);
	deimos.setColour(glm::vec3(0.8f, 0.8f, 0.8f));
}

void PlanetManager::createPhobos() {
	phobos.setName("Phobos");
	phobos.setParent(&mars);
	phobos.setScale(glm::vec3(globalScale*0.15f)); // 0.00097 earth (rounded up to 0.1)
	phobos.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed * 27.3f * 5); // moon*86, rounded to moon*5
	phobos.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
	phobos.setOrbitDistance(glm::vec3(globalDistScale * 0.10f, 0.0f, 0.0f)); // tiny 9k km (0.10 earth-sun to see it)
	phobos.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 18.0f); // tiny 0.3 days (rounded up to 1.5x moon)
	phobos.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 1.093f);
	phobos.setColour(glm::vec3(0.8f, 0.8f, 0.8f));
}

void PlanetManager::createJupiter() {
	jupiter.setName("Jupiter");
	jupiter.setParent(&sol);
	jupiter.setScale(glm::vec3(globalScale*11.2f)); // 11.2 earth
	jupiter.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*2.4f);
	jupiter.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 3.13f);
	jupiter.setOrbitDistance(glm::vec3(globalDistScale * 5.2f, 0.0f, 0.0f)); // 5.2 earth-sun distance
	jupiter.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 0.08f); // 11.86 earth years
	jupiter.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 6.0f);
	jupiter.setColour(glm::vec3(1.0f, 0.5f, 0.0f));
}

void PlanetManager::createGanymede() {
	ganymede.setName("Ganymede");
	ganymede.setParent(&jupiter);
	ganymede.setScale(glm::vec3(globalScale*0.413f)); // 0.413 earths
	ganymede.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*27.3f * 3.8f); // moon*3.8
	ganymede.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
	ganymede.setOrbitDistance(glm::vec3(globalDistScale * 0.65f, 0.0f, 0.0f)); // 2.8 moon-earth distance (capped at 0.65 earth-sun)
	ganymede.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 18.0f); // moon*3.8 capped at 1.5x moon
	ganymede.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
	ganymede.setColour(glm::vec3(0.6f, 0.5f, 0.1f));
}

void PlanetManager::createCallisto() {
	callisto.setName("Callisto");
	callisto.setParent(&jupiter);
	callisto.setScale(glm::vec3(globalScale*0.378f)); // 0.378 earths
	callisto.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*27.3f * 1.64f); // moon*1.64
	callisto.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
	callisto.setOrbitDistance(glm::vec3(globalDistScale * 0.5f, 0.0f, 0.0f)); // 4.9 moon-earth distance (capped at 0.5 earth-sun)
	callisto.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 12.0f); // moon*1.64 capped at 1.0x moon
	callisto.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 2.2f);
	callisto.setColour(glm::vec3(0.6f, 0.5f, 0.1f));
}

void PlanetManager::createSaturn() {
	saturn.setName("Saturn");
	saturn.setParent(&sol);
	saturn.setScale(glm::vec3(globalScale*9.45f)); // 9.45 earth
	saturn.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*2.2f);
	saturn.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 26.73f);
	saturn.setOrbitDistance(glm::vec3(globalDistScale * 9.58f, 0.0f, 0.0f)); // 9.58 earth-sun distance
	saturn.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 0.034f); // 29.45 earth years
	saturn.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 5.51f);
	saturn.setColour(glm::vec3(0.8f, 0.8f, 0.0f));
}

void PlanetManager::createRingOfSaturn() {
	ringOfSaturn.setName("RingOfSaturn");
	ringOfSaturn.setParent(&sol);
	ringOfSaturn.setScale(glm::vec3(globalScale*9.45f * 1.8f, globalScale*9.45f * 0.01f , globalScale*9.45f * 1.8f)); // 9.45 earth
	ringOfSaturn.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*2.2f);
	ringOfSaturn.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 26.73f);
	ringOfSaturn.setOrbitDistance(glm::vec3(globalDistScale * 9.58f, 0.0f, 0.0f)); // 9.58 earth-sun distance
	ringOfSaturn.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 0.034f); // 29.45 earth years
	ringOfSaturn.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 5.51f);
	ringOfSaturn.setColour(glm::vec3(0.5f, 0.5f, 0.0f));
}

void PlanetManager::createTitan() {
	titan.setName("Titan");
	titan.setParent(&saturn);
	titan.setScale(glm::vec3(globalScale*0.4f)); // 0.4 earths
	titan.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*27.3f*1.7f);
	titan.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
	titan.setOrbitDistance(glm::vec3(globalDistScale * 0.65f, 0.0f, 0.0f)); // 0.0026 earth-sun distance (0.15 to see it)
	titan.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 12.0f*1.7f); // 1.7*moon
	titan.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.3f);
	titan.setColour(glm::vec3(1.0f, 0.7f, 0.0f));
}
void PlanetManager::createRhea() {
	rhea.setName("Rhea");
	rhea.setParent(&saturn);
	rhea.setScale(glm::vec3(globalScale*0.15f)); // 0.44 moons, capped at 0.15 earths
	rhea.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*27.3f*6);
	rhea.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.3f);
	rhea.setOrbitDistance(glm::vec3(globalDistScale * 0.4f, 0.0f, 0.0f)); 
	rhea.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 12.0f*2); // x6 moon capped at x2
	rhea.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
	rhea.setColour(glm::vec3(1.0f, 1.0f, 1.0f));
}

void PlanetManager::createUranus() {
	uranus.setName("Uranus");
	uranus.setParent(&sol);
	uranus.setScale(glm::vec3(globalScale*4.0f)); // 4 earth
	uranus.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*1.39f);
	uranus.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 97.7f);
	uranus.setOrbitDistance(glm::vec3(globalDistScale * 19.189f, 0.0f, 0.0f)); // 19.189 earth-sun distance
	uranus.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 0.0119f); // 84 earth years
	uranus.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 5.51f);
	uranus.setColour(glm::vec3(0.0f, 0.8f, 0.0f));
}

void PlanetManager::createTitania() {
	titania.setName("Titania");
	titania.setParent(&uranus);
	titania.setScale(glm::vec3(globalScale*0.1235f)); // 0.1235 earths
	titania.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*27.3f*2.0f);
	titania.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
	titania.setOrbitDistance(glm::vec3(globalDistScale * 0.30f, 0.0f, 0.0f));
	titania.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 12.0f * 2.0f);
	titania.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.3f);
	titania.setColour(glm::vec3(0.8f, 0.8f, 0.8f));
}

void PlanetManager::createOberon() {
	oberon.setName("Oberon");
	oberon.setParent(&uranus);
	oberon.setScale(glm::vec3(globalScale*0.12f)); // 0.12 earths
	oberon.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*27.3f*3.1f);
	oberon.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
	oberon.setOrbitDistance(glm::vec3(globalDistScale * 0.20f, 0.0f, 0.0f)); 
	oberon.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 12.0f * 3.1f);
	oberon.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
	oberon.setColour(glm::vec3(1.0f, 0.8f, 0.8f));
}

void PlanetManager::createNeptune() {
	neptune.setName("Neptune");
	neptune.setParent(&sol);
	neptune.setScale(glm::vec3(globalScale*3.88f)); // 3.88 earth
	neptune.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*1.49f); 
	neptune.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 28.32f);
	neptune.setOrbitDistance(glm::vec3(globalDistScale * 30.07f, 0.0f, 0.0f)); // 30.07 earth-sun distance
	neptune.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 0.0061f); // 164.8 earth years
	neptune.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 6.43f);
	neptune.setColour(glm::vec3(0.0f, 0.8f, 0.0f));
}

void PlanetManager::createTriton() {
	triton.setName("Triton");
	triton.setParent(&neptune);
	triton.setScale(glm::vec3(globalScale*0.212f)); // 0.212 earths
	triton.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*27.3f*4);
	triton.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.5f);
	triton.setOrbitDistance(glm::vec3(globalDistScale * 0.25f, 0.0f, 0.0f));
	triton.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 12.0f * 2); 
	triton.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 128.0f);
	triton.setColour(glm::vec3(0.8f, 0.7f, 0.4f));
}

void PlanetManager::createProteus() {
	proteus.setName("Proteus");
	proteus.setParent(&neptune);
	proteus.setScale(glm::vec3(globalScale*0.2f)); // tiny <500km rounded up to 0.2 earth
	proteus.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), globalRotateSpeed*27.3f*4.0f);
	proteus.setPlanetTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
	proteus.setOrbitDistance(glm::vec3(globalDistScale * 0.2f, 0.0f, 0.0f));
	proteus.setOrbit(glm::vec3(0.0f, 1.0f, 0.0f), globalOrbitSpeed * 12.0f*2); 
	proteus.setOrbitTilt(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
	proteus.setColour(glm::vec3(0.8f, 0.8f, 0.8f));
}