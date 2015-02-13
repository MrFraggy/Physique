#pragma once

#include <memory>
#include <vector>
#include <physic/masses/masse.h>
#include <physic/forces/force.h>
#include <physic/link.h>

#include <physic/masses/masses.h>

class Modeleur
{
public:
	Modeleur();
	void update();

#if USE_DATA_ORIENTED
	int addMass(const glm::vec3& pos, float mass, bool fix = false, float radius = 1.f, const glm::vec3& color = glm::vec3(0,1,0));
protected:
	Masses masses;

#else

	void addMasse(MassePtr m);
	void addLink(LinkPtr l);
	void addMacroForce(ForcePtr f);
	
protected:
	std::vector<MassePtr> masses;
	std::vector<LinkPtr> links;
	std::vector<ForcePtr> forces;

#endif
};