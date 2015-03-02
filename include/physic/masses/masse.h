#pragma once

#ifndef C_PMAT_H
#define C_PMAT_H

#include <glm/glm.hpp>
#include <physic/constants.h>
#include <memory>
#include <vector>

class Link;
class Masse
{
public:
	Masse(const glm::vec3& p, float masse, const glm::vec3& c);

	void addForce(const glm::vec3& p);
	void update();

	glm::vec3 getPosition();
	glm::vec3 getVitesse();
	float getMasse();
	glm::vec3 getColor();
	float getRadius();
	
	void addLink(Link* l);
	void removeLink(Link* l);
	const std::vector<Link*>& getLinks();

protected:
	virtual void onUpdate() = 0;

	glm::vec3 pos, vit, frc, color;
	float masse, rayon;

	std::vector<Link*> links;
};

typedef std::shared_ptr<Masse> MassePtr;


#endif