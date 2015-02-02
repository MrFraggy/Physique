#include <physic/forces/vent.h>
#include <glm/gtc/random.hpp>
#include <iostream>

Vent::Vent(const glm::vec3& dir) :
	Force(ForceIdentifier::Vent), direction(dir)
{

}

void Vent::onUpdate(Masse* m1, Masse* m2)
{
	glm::vec3 intensity = glm::linearRand(glm::vec3(0,0,0),glm::vec3(1.5,1.5,1.5));
	glm::vec3 tmpdir = direction + glm::linearRand(glm::vec3(-50,-50,-50),glm::vec3(50,50,50));
	//std::cout << direction.x << " " << direction.y << " " << direction.z << std::endl;
	if(m1)
		m1->addForce(tmpdir*intensity);
	if(m2)
		m2->addForce(tmpdir*intensity);
}