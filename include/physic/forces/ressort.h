#pragma once

#ifndef C_RESSORT_HPP
#define C_RESSORT_HPP

#include <physic/forces/force.h>

class Ressort : public Force
{
public:
	Ressort(float raideur = 10000);
	void onUpdate(Masse* m1, Masse* m2);
	void init(Masse* m1, Masse* m2);

protected:
	float raideur;
	float longueurAVide;
};

typedef std::shared_ptr<Ressort> RessortPtr;

#endif