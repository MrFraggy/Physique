#include <physic/forces/constante.h>


ForceConstante::ForceConstante(const glm::vec3& force) :
Force(ForceIdentifier::Constante), force(force)
{

}

void ForceConstante::onUpdate(Masse* m1, Masse* m2)
{
	if(m1)
		m1->addForce(force);
	if(m2)
		m2->addForce(force);
}