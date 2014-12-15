#include <physic/modeleur.h>

void Modeleur::update()
{
	for(auto& l: links)
		l->update();
	for(auto& p: masses)
	{
		for(auto& f: forces)
			f->onUpdate(p.get(), nullptr);

		p->update();
	}
}

void Modeleur::addMasse(MassePtr m)
{
	masses.push_back(std::move(m));
}
	
void Modeleur::addLink(LinkPtr l)
{
	links.push_back(std::move(l));
}

void Modeleur::addMacroForce(ForcePtr f)
{
	forces.push_back(std::move(f));
}