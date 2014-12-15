#pragma once

#include <memory>
#include <vector>
#include <physic/masse.h>
#include <physic/link.h>

class Modeleur
{
public:
	void update();

	void addMasse(std::shared_ptr<Masse> m);
	void addLink(std::shared_ptr<Link> l);
	
protected:
	std::vector<std::shared_ptr<Masse>> masses;
	std::vector<std::shared_ptr<Link>> links;
};