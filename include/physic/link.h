#pragma once

#ifndef C_LINK_H
#define C_LINK_H

#include <glm/glm.hpp>
#include <physic/masses/masse.h>
#include <physic/forces/force.h>
#include <memory>
#include <vector>


class Link
{
public:
	Link(Masse* m1, Masse* m2);

	void update();

	void addComponent(const std::shared_ptr<Force>& f);

protected:
	Masse* masses[2];
	float longueurAVide;
	std::vector<std::shared_ptr<Force>> components;

	// Seuils divers, flags divers
};

typedef std::shared_ptr<Link> LinkPtr;


LinkPtr getRessortFrein(Masse* m1, Masse* m2);

/*
class RessortFreinLink : public Link
{
public:
	RessortFreinLink(Masse* m1, Masse* m2) : Link(m1,m2) {}

protected:
	void onUpdate()
	{
		glm::vec3 dir = masses[0]->getPosition()-masses[1]->getPosition();
		float dist = glm::length(dir);

		if(dist < 0.001f)
			return;

		float forceRessort = -raideur*(1-(longueurAVide/dist));
		masses[0]->addForce(dir*forceRessort);
		masses[1]->addForce(-dir*forceRessort);

		glm::vec3 forceFrein = (masses[0]->getVitesse() - masses[1]->getVitesse()) * (viscosite/Fe);

		masses[0]->addForce(-forceFrein);
		masses[1]->addForce(forceFrein);
	}
};*/

#endif