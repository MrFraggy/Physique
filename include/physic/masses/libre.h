#pragma once
#ifndef C_MASSELIBRE_HPP
#define C_MASSELIBRE_HPP

#include <physic/masses/masse.h>

class MasseLibre : public Masse
{
public:
	MasseLibre(const glm::vec3& p, float m) : Masse(p,m, glm::vec3(0,1,0)) {}
protected:
	void onUpdate()
	{
		vit += frc*dt/masse;
		pos += vit*dt;
		frc = glm::vec3(0,0,0);
	}
};

#endif