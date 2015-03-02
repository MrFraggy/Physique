#include <physic/masses/masse.h>
#include <algorithm>

Masse::Masse(const glm::vec3& pos, float masse, const glm::vec3& c) : 
	pos(pos), 
	masse(masse),
	color(c),
	rayon(.05f)
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

float Masse::getRadius()
{
	return rayon;
}

void Masse::addLink(Link* l)
{
	links.push_back(l);
}

void Masse::removeLink(Link* l)
{
	auto it = std::find(links.begin(), links.end(), l);
	if(it != links.end())
		links.erase(it);
}

const std::vector<Link*>& Masse::getLinks()
{
	return links;
}