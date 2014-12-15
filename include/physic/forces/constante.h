#pragma once

#ifndef C_CONSTANTE_HPP
#define C_CONSTANTE_HPP

#include <physic/forces/force.h>

class ForceConstante: public Force
{
public:
	ForceConstante(const glm::vec3& force);
	void onUpdate(Masse* m1, Masse* m2);

protected:
	glm::vec3 force;
};

typedef std::shared_ptr<ForceConstante> ForceConstantePtr;

#endif