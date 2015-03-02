#pragma once

#include <physic/masses/masses.h>
#include <PartyKel/glm.hpp>
#include <iostream>

#include <cuda/cudaFunctions.hpp>

class SpringBreaks {
public:
	SpringBreaks(Masses& masses) : masses(masses) {}

	int create(int massId1, int massId2, float baseLength, float viscosity = 100.f, bool removable = false)
	{
		int id = baseLengths.size();
		massesIds.push_back(massId1);
		massesIds.push_back(massId2);
		baseLengths.push_back(baseLength);
		viscosities.push_back(viscosity);
		areRemovable.push_back(removable);
		return id;
	}

	bool remove(int id)
	{
		if(id < 0 || id >= baseLengths.size() || !areRemovable[id])
			return false;
		
		massesIds.erase(massesIds.begin()+id);
		massesIds.erase(massesIds.begin()+id);
		baseLengths.erase(baseLengths.begin()+id);
		viscosities.erase(viscosities.begin()+id);
		areRemovable.erase(areRemovable.begin()+id);
		return true;
	}

	void update() {
		const float raideur = 10000;
		auto& forces = masses.getForces();
		auto& velocities = masses.getVelocities();
		auto& positions = masses.getPositions();
		/*const int size = massesIds.size()/2;
		for(int i = 0; i<size; ++i)
		{
			int id1 = massesIds[i*2], id2 = massesIds[i*2+1];
			glm::vec3 forcesAccumulatorM1, forcesAccumulatorM2;

			// Apply spring force
			glm::vec3 dir = positions[id1]-positions[id2];
			float dist = glm::length(dir);
			float forceRessort = -raideur*(1-(baseLengths[i]/std::max(0.001f, dist)));
			//std::getchar();
			forcesAccumulatorM1 += dir*forceRessort;
			forcesAccumulatorM2 += -dir*forceRessort;

			// Apply Brake force
			glm::vec3 forceFrein = (velocities[id1] - velocities[id2]) * (viscosities[i]/Fe);
			forcesAccumulatorM1 -= forceFrein;
			forcesAccumulatorM2 += forceFrein;


			// Operations atomique
			forces[id1] += forcesAccumulatorM1;
			forces[id2] += forcesAccumulatorM2;
			//std::cout << forcesAccumulatorM1 << std::endl;
		}*/
		cudaSpringbreak(massesIds, baseLengths);
	}

	std::vector<int>& getMassesIds() { return massesIds; }
	std::vector<bool>& getAreRemovables() { return areRemovable; }

protected:
	Masses& masses;
	std::vector<int> massesIds; // link
	std::vector<float> baseLengths;
	std::vector<float> viscosities;
	std::vector<bool> areRemovable;
};