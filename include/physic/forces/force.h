#pragma once

#ifndef C_FORCE_HPP
#define C_FORCE_HPP

#include <physic/masses/masse.h>

class Force
{
public:
	virtual void init(Masse* m1, Masse* m2) {};
	virtual void onUpdate(Masse* m1, Masse* m2) = 0;
};

typedef std::shared_ptr<Force> ForcePtr;

#endif