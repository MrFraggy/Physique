#pragma once

#ifndef C_PMAT_H
#define C_PMAT_H

#include <glm/glm.hpp>
#include <physic/constants.h>

class Masse
{
public:
	Masse(const glm::vec3& p, float masse, const glm::vec3& c);

	void addForce(const glm::vec3& p);
	void update();

	glm::vec3 getPosition();
	glm::vec3 getVitesse();
	float getMasse();
	glm::vec3 getColor();

protected:
	virtual void onUpdate() = 0;

	glm::vec3 pos, vit, frc, color;
	float masse, rayon;
};


class MasseFixe : public Masse
{
public:
	MasseFixe(const glm::vec3& p) : Masse(p, 1.f, glm::vec3(1,0,0)) {} 
protected:
	void onUpdate() 
	{
		frc = glm::vec3(0,0,0);
	}
};

class MasseLibre : public Masse
{
public:
	MasseLibre(const glm::vec3& p, float m) : Masse(p,m, glm::vec3(0,1,0)) {}
protected:
	void onUpdate()
	{
		vit += frc*dt/masse;
		pos += vit*dt;
		frc = glm::vec3(0,G,0);
	}
};

#endif