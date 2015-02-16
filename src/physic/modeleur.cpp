#include <physic/modeleur.h>
#include <iostream>

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