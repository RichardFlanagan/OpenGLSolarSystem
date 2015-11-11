#ifndef PLANET_MANAGER_H
#define PLANET_MANAGER_H
#include "PlanetaryBody.h"
#include "PlanetManager.h"
#include <vector>

class PlanetManager {
public:
	PlanetManager();
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
	//PlanetaryBody deimos;
	//PlanetaryBody phobos;

	PlanetaryBody jupiter;
	void createJupiter();
	//PlanetaryBody ganymede;
	//PlanetaryBody callisto;
	//PlanetaryBody io;
	//PlanetaryBody europa;

	PlanetaryBody saturn;
	void createSaturn();
	//PlanetaryBody titan;
	//PlanetaryBody rhea;
	//PlanetaryBody lapetus;
	//PlanetaryBody dione;

	PlanetaryBody uranus;
	void createUranus();
	//PlanetaryBody tiania;
	//PlanetaryBody oberon;
	//PlanetaryBody umbriel;
	//PlanetaryBody ariel;

	PlanetaryBody neptune;
	void createNeptune();
	//PlanetaryBody triton;
	//PlanetaryBody proteus;
	//PlanetaryBody nereid;
	//PlanetaryBody larissa;

};

#endif // PLANETARY_MANAGER_H
