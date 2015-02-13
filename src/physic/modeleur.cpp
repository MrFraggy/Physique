#include <physic/modeleur.h>
#include <iostream>

Modeleur::Modeleur()
{
#if USE_DATA_ORIENTED
	masses.setUpdateFunc([](bool fxd, glm::vec3& frc, glm::vec3& vel, glm::vec3& frc) -> void{
		if(!fxd)
		{
			frc = glm::vec3(0,0,0);
		}
		else 
		{
			vit += frc*dt/masse;
			pos += vit*dt;
			frc = glm::vec3(0,0,0);
		}
	});
#endif
}

void Modeleur::update()
{
#if USE_DATA_ORIENTED
	masses.update();
#else
	for(auto& l: links)
		l->update();

	for(int i = 0; i<masses.size(); ++i)
	{
		for(auto& f: forces)
			f->onUpdate(masses[i].get(), nullptr);

		masses[i]->update();

#if USE_AUTOCOLLISION
		auto& masseLinks = masses[i]->getLinks();

		for(int j = i+1; j<masses.size(); ++j)
		{
			glm::vec3 dir = masses[j]->getPosition() - masses[i]->getPosition();
			float dist = glm::length(dir);
			if(dist < 0.3f)
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

			}else if(dist > 0.7f)
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
		std::cout << links.size() << std::endl;
#endif
	}
#endif
}


#if USE_DATA_ORIENTED

int Modeleur::addMass(const glm::vec3& pos, float mass, bool fix, float radius, const glm::vec3& color)
{
	return masses.create(pos,mass,fix,radius,color);
}

#else

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
#endif