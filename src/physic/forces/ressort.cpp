#include <physic/forces/ressort.h>

Ressort::Ressort(float raideur) : 
	Force(ForceIdentifier::Ressort), raideur(raideur) 
{}

void Ressort::onUpdate(Masse* m1, Masse* m2)
{
	glm::vec3 dir = m1->getPosition()-m2->getPosition();
	float dist = glm::length(dir);

	if(dist < 0.001f)
		return;

	float forceRessort = -raideur*(1-(longueurAVide/dist));
	m1->addForce(dir*forceRessort);
	m2->addForce(-dir*forceRessort);
}

void Ressort::init(Masse* m1, Masse* m2)
{
	longueurAVide = glm::length(m1->getPosition()-m2->getPosition());
}