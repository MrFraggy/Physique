#pragma once

#ifndef C_FREIN_HPP
#define C_FREIN_HPP

#include <physic/forces/force.h>

class Frein : public Force
{
public:
	Frein(float viscosite = 100);
	void onUpdate(Masse* m1, Masse* m2);
protected:
	float viscosite;
};

typedef std::shared_ptr<Frein> FreinPtr;

#endif