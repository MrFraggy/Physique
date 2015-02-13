#pragma once

#include <memory>
#include <vector>
#include <physic/masses/masse.h>
#include <physic/forces/force.h>
#include <physic/link.h>

#include <physic/masses/masses.h>
#include <physic/springbreaks.h>

class Modeleur
{
public:
	Modeleur();
	void update();

	int addMass(const glm::vec3& pos, float mass, bool fix = false, float radius = 1.f, const glm::vec3& color = glm::vec3(0,1,0));
	Masses& getMasses();
	SpringBreaks& getSpringBreaks();
protected:
	Masses masses;
	SpringBreaks springBreaks;
};