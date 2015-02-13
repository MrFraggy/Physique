#include <physic/modeleur.h>
#include <iostream>

Modeleur::Modeleur() : springBreaks(masses)
{
	masses.setUpdateFunc([](bool fxd, glm::vec3& frc, glm::vec3& vel, glm::vec3& frc) -> void{
		if(!fxd)
		{
			frc = glm::vec3(0,0,0);
		}
		else 
		{
			vit += frc*dt/masse;
			pos += vit*dt;
			frc = glm::vec3(0,0,0);
		}
	});
}

void Modeleur::update()
{
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