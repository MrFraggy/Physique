#pragma once

#ifndef C_LINK_H
#define C_LINK_H

#include <glm/glm.hpp>
#include <physic/masse.h>

class Link
{
public:
	Link(Masse* m1, Masse* m2, float raideur = 10000, float viscosite = 1);

	void update();

protected:
	virtual void onUpdate() = 0;

	Masse* masses[2];
	glm::vec3 force;
	float raideur;
	float viscosite;
	float longueurAVide;

	// Seuils divers, flags divers
};

class ConstantForceLink : public Link
{
protected:
	void onUpdate();
};

class RessortLink : public Link
{
public:
	RessortLink(Masse* m1, Masse* m2) : Link(m1,m2) {}
protected:
	void onUpdate()
	{
		glm::vec3 v = masses[0]->getPosition()-masses[1]->getPosition();
		float dist = glm::length(v);

		if(dist < 0.001f)
			return;

		float f = -raideur*(1-(longueurAVide/dist));
		masses[0]->addForce(v*f);
		masses[1]->addForce(-v*f);		
	}
};

class FreinLink : public Link
{
protected:
	void onUpdate();
};

class RessortFreinLink : public Link
{
protected:
	void onUpdate();
};

#endif