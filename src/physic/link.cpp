#include <physic/link.h>
#include <physic/forces/frein.h>
#include <physic/forces/ressort.h>

Link::Link(Masse* m1, Masse* m2)
{
	masses[0] = m1;
	masses[1] = m2;
	m1->addLink(this);
	m2->addLink(this);
}

Link::~Link()
{
	if(masses[0])
		masses[0]->removeLink(this);
	if(masses[1])
		masses[1]->removeLink(this);
}
void Link::update()
{
	for(auto& m: components)
	{
		m->onUpdate(masses[0], masses[1]);
	}
}

void Link::addComponent(const std::shared_ptr<Force>& f)
{
	components.push_back(f);
	f->init(masses[0], masses[1]);
}

bool Link::hasComponent(ForceIdentifier id)
{
	for(auto& m: components)
		if(m->getType() == id)
			return true;
	return false;
}

bool Link::hasMass(Masse* m)
{
	return masses[0] == m || masses[1] == m;
}

LinkPtr createRessortFrein(Masse* m1, Masse* m2)
{
    LinkPtr l(new Link(m1, m2));
    l->addComponent(FreinPtr(new Frein()));
    l->addComponent(RessortPtr(new Ressort()));
    return l;
} 