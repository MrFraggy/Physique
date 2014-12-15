#include <physic/link.h>

Link::Link(Masse* m1, Masse* m2)
{
	masses[0] = m1;
	masses[1] = m2;
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