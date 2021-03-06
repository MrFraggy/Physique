#pragma once

#ifndef C_FORCE_HPP
#define C_FORCE_HPP

#include <physic/masses/masse.h>
#include <physic/forces/identifiers.h>
class Force
{
public:
	Force(ForceIdentifier t) : type(t) {}
	virtual void init(Masse* m1, Masse* m2) {};
	virtual void onUpdate(Masse* m1, Masse* m2) = 0;
	virtual void onUpdateBegin() {};

	ForceIdentifier getType() const { return type; }
protected:
	ForceIdentifier type;
};

typedef std::shared_ptr<Force> ForcePtr;

#endif