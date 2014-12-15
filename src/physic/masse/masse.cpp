#include <physic/masses/masse.h>

Masse::Masse(const glm::vec3& pos, float masse, const glm::vec3& c) : 
	pos(pos), 
	masse(masse),
	color(c),
	rayon(1)
{

}

void Masse::addForce(const glm::vec3& force)
{
	frc += force;
}

void Masse::update()
{
	onUpdate();
}

glm::vec3 Masse::getPosition()
{
	return pos;
}

glm::vec3 Masse::getVitesse()
{
	return vit;
}

float Masse::getMasse()
{
	return masse;
}

glm::vec3 Masse::getColor()
{
	return color;
}