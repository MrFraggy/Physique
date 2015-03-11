#include <physic/forces/vent.h>
#include <glm/gtc/random.hpp>
#include <iostream>
#include <random>
#define EPSILON 0.001

Vent::Vent(const glm::vec3& dir) :
	Force(ForceIdentifier::Vent), direction(dir), variation(glm::vec3(1))
{}

void Vent::onUpdateBegin()
{
	if(abs(variation.x) < EPSILON || abs(variation.y) < EPSILON || abs(variation.z) < EPSILON)
		variation = glm::linearRand(glm::vec3(-2), glm::vec3(2));
	else
		variation -= glm::normalize(variation);
	
	std::cout << " variation : " << variation.x << " " << variation.y << " " << variation.z << std::endl;

	// glm::vec3 intensity = glm::linearRand(glm::vec3(0,0,0),glm::vec3(1.5,1.5,1.5));
	direction += glm::normalize(variation);
	std::cout << " direction " << direction.x << " " << direction.y << " " << direction.z << std::endl;
}

void Vent::onUpdate(Masse* m1, Masse* m2)
{
	if(m1)
		m1->addForce(direction);
	if(m2)
		m2->addForce(direction);
}