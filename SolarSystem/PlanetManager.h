#ifndef PLANET_MANAGER_H
#define PLANET_MANAGER_H
#include "PlanetaryBody.h"
#include "PlanetManager.h"
#include <vector>

class PlanetManager {
public:
	PlanetManager();
	~PlanetManager() {};

	std::vector<PlanetaryBody*>* getPlanetaryBodies();

private:
	std::vector<PlanetaryBody*> planetaryBodies;
	void populatePlanetList();
	float globalScale;
	float globalRotateSpeed;
	float globalOrbitSpeed;
	float globalDistScale;

	PlanetaryBody sol;
	void createSol();

	PlanetaryBody mercury;
	void createMercury();

	PlanetaryBody venus;
	void createVenus();

	PlanetaryBody earth;
	void createEarth();
	PlanetaryBody luna;
	void createLuna();

	PlanetaryBody mars;
	void createMars();
	PlanetaryBody deimos;
	void createDeimos();
	PlanetaryBody phobos;
	void createPhobos();

	PlanetaryBody jupiter;
	void createJupiter();
	PlanetaryBody ganymede; 
	void createGanymede();
	PlanetaryBody callisto;
	void createCallisto();

	PlanetaryBody saturn;
	void createSaturn();
	PlanetaryBody titan;
	void createTitan();
	PlanetaryBody rhea;
	void createRhea();

	PlanetaryBody uranus;
	void createUranus();
	PlanetaryBody titania;
	void createTitania();
	PlanetaryBody oberon;
	void createOberon();

	PlanetaryBody neptune;
	void createNeptune();
	PlanetaryBody triton;
	void createTriton();
	PlanetaryBody proteus;
	void createProteus();

};

#endif // PLANETARY_MANAGER_H
