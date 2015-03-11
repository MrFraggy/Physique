#pragma once

#ifndef C_VENT_HPP
#define C_VENT_HPP

#include <physic/forces/force.h>

class Vent: public Force
{
public:
	Vent(const glm::vec3& dir);
	void onUpdateBegin();
	void onUpdate(Masse* m1, Masse* m2);

protected:
	glm::vec3 direction;
	glm::vec3 variation;
};

typedef std::shared_ptr<Vent> VentPtr;

#endif