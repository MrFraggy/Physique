#include <physic/link.h>

Link::Link(Masse* p1, Masse* p2, float raideur, float viscosite) :
	raideur(raideur), viscosite(viscosite)
{
	masses[0] = p1;
	masses[1] = p2;
	longueurAVide = glm::length(masses[0]->getPosition()-masses[1]->getPosition());
}

void Link::update()
{
	onUpdate();
}