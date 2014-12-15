#pragma once
#ifndef C_MASSEFIXE_HPP
#define C_MASSEFIXE_HPP

#include <physic/masses/masse.h>

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

#endif