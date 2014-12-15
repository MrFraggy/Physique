#pragma once

#include <memory>
#include <vector>
#include <physic/masses/masse.h>
#include <physic/forces/force.h>
#include <physic/link.h>

class Modeleur
{
public:
	void update();

	void addMasse(MassePtr m);
	void addLink(LinkPtr l);
	void addMacroForce(ForcePtr f);
	
protected:
	std::vector<MassePtr> masses;
	std::vector<LinkPtr> links;
	std::vector<ForcePtr> forces;
};