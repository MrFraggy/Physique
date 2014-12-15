#pragma once

#include <memory>
#include <vector>
#include <physic/masses/masse.h>
#include <physic/link.h>

class Modeleur
{
public:
	void update();

	void addMasse(MassePtr m);
	void addLink(LinkPtr l);
	
protected:
	std::vector<MassePtr> masses;
	std::vector<LinkPtr> links;
};