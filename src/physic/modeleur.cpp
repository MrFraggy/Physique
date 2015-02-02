#include <physic/modeleur.h>

void Modeleur::update()
{
	for(auto& l: links)
		l->update();
	for(int i = 0; i<masses.size(); ++i)
	{
		for(auto& f: forces)
			f->onUpdate(masses[i].get(), nullptr);

		masses[i]->update();
		auto& masseLinks = masses[i]->getLinks();

		for(int j = i+1; j<masses.size(); ++j)
		{
			glm::vec3 dir = masses[j]->getPosition() - masses[i]->getPosition();
			float dist = glm::length(dir);
			if(dist < 0.2f)
			{
				bool hasFrein = false, hasRessort = false;

				for(auto& l: masseLinks)
				{
					if(l->hasMass(masses[j].get()) && l->hasComponent(ForceIdentifier::Frein))
						hasFrein = true;
					else if(l->hasMass(masses[j].get()) && l->hasComponent(ForceIdentifier::Ressort))
						hasRessort = true;
				}
				if(!hasFrein && !hasRessort)
					links.push_back(createRessortFrein(masses[i].get(), masses[j].get()));
			}else if(dist > 1.f)
			{
				Link* toRemove = nullptr;
				for(auto* ml : masseLinks)
				{
					if(ml->hasMass(masses[j].get()))
					{
						toRemove = ml;
						break;
					}
				}

				if(toRemove)
				{
					for(auto it = links.begin(); it != links.end(); ++it)
					{
						if(it->get() == toRemove)
						{
							links.erase(it);
							break;
						}
					}
				}
			}
		}
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