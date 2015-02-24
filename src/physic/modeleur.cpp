#include <physic/modeleur.h>
#include <iostream>

static const float MIN_DIST = 0.01f;
static const float MAX_DIST = 1.0f;

Modeleur::Modeleur() : springBreaks(masses), constantForces(masses)
{
	masses.setUpdateFunction([](bool fxd, glm::vec3& pos, glm::vec3& vel, glm::vec3& frc, float mass) -> void{
		if(!fxd)
		{
			vel += frc*dt/mass;
			pos += vel*dt;
		}
		frc = glm::vec3(0,0,0);
	});
}

void Modeleur::update()
{
	springBreaks.update();
	constantForces.update();
	masses.update();

	// Autocollisions
	/*auto& positions = masses.getPositions();
	auto& radius = masses.getRadius();
	auto& links = springBreaks.getMassesIds();
	for(uint32_t i = 0 ; i<positions.size(); ++i)
	{
		for(uint32_t j = i+1; j<positions.size(); ++j)
		{
			glm::vec3 dir = positions[j] - positions[i];
			float dist = glm::length(dir);
			bool hasFrein = false;
			float minDist = radius[i]+radius[j];
			float maxDist = (radius[i]+radius[j])*3;
			if(dist < minDist)
			{
				for(uint32_t k = 0; k<links.size(); k += 2)
				{
					if((links[k] == i && links[k+1] == j) || (links[k] == j && links[k+1] == i))
					{
						hasFrein = true;
						break;
					}
				}
				if(!hasFrein)
					springBreaks.create(i,j,dist, 100.f, true);
			}
		}
	}
	for(uint32_t k = 0; k<links.size(); k += 2)
	{
		glm::vec3 dir = positions[k] - positions[k+1];
		float maxDist = (radius[k]+radius[k+1])*3;
		float dist = glm::length(dir);
		if(dist < maxDist)
			continue;

		if(springBreaks.remove(k))
			--k;
	}*/
}

int Modeleur::addMass(const glm::vec3& pos, float mass, bool fix, float radius, const glm::vec3& color)
{
	return masses.create(pos,mass,fix,radius,color);
}

Masses& Modeleur::getMasses()
{
	return masses;
}

SpringBreaks& Modeleur::getSpringBreaks()
{
	return springBreaks;
}

ConstantForces& Modeleur::getConstantForces()
{
	return constantForces;
}