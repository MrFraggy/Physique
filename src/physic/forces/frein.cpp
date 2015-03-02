#include <physic/forces/frein.h>

Frein::Frein(float viscosite) : 
	Force(ForceIdentifier::Frein), viscosite(viscosite)
{}

void Frein::onUpdate(Masse* m1, Masse* m2)
{
	glm::vec3 forceFrein = (m1->getVitesse() - m2->getVitesse()) * (viscosite);

	m1->addForce(-forceFrein);
	m2->addForce(forceFrein);
}