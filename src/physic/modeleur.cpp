#include <physic/modeleur.h>

void Modeleur::update()
{
	for(auto& l: links)
		l->update();
	for(auto& p: masses)
		p->update();
}

void Modeleur::addMasse(std::shared_ptr<Masse> m)
{
	masses.push_back(std::move(m));
}
	
void Modeleur::addLink(std::shared_ptr<Link> l)
{
	links.push_back(std::move(l));
}