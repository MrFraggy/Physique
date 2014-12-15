#include <physic/link.h>

Link::Link(Masse* m1, Masse* m2)
{
	masses[0] = m1;
	masses[1] = m2;
}

void Link::update()
{
	for(auto& m: components)
	{
		m->onUpdate(masses[0], masses[1]);
	}
}

void Link::addComponent(const std::shared_ptr<Force>& f)
{
	components.push_back(f);
	f->init(masses[0], masses[1]);
}





Ressort::Ressort(float raideur) : 
	raideur(raideur) 
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





Frein::Frein(float viscosite) : 
	viscosite(viscosite)
{}

void Frein::onUpdate(Masse* m1, Masse* m2)
{
	glm::vec3 forceFrein = (m1->getVitesse() - m2->getVitesse()) * (viscosite/Fe);

	m1->addForce(-forceFrein);
	m2->addForce(forceFrein);
}