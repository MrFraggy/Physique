#include <physic/modeleur.h>

static const float L0 = .05f * 2;

void Modeleur::update()
{
	for(auto& l: links)
		l->update();
	for(auto& m: masses)
	{
		for(auto& f: forces)
			f->onUpdate(m.get(), nullptr);

		m->update();
		/*auto& masseLinks = masses[i]->getLinks();

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
		}*/
	}

	for(int i = 0; i<masses.size(); ++i)
	{
		for(int j = i+1; j<masses.size(); ++j)
		{
			auto p1 = masses[i]->getPosition();
			auto p2 = masses[j]->getPosition();
			auto dir = p2-p1;
			float dist = glm::length(dir);
			if(dist > L0)
				continue;

			float forceRessort = -1000000 * (L0-dist);
			masses[i]->addForce(dir*forceRessort);
			masses[j]->addForce(-dir*forceRessort);

			// Maybe useless ??? Add break
			auto vit1 = masses[i]->getVitesse();
			auto vit2 = masses[j]->getVitesse();
			auto forceFrein = (vit1 - vit2) * 30.f;
			masses[i]->addForce(-forceFrein);
			masses[j]->addForce(forceFrein);
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