#pragma once
#include "../../../Engine/Engine.h"
#include "../Transform.hpp"
//‹…‘Ì‚Ì’è‹`
class Sphere
{
public:
	float radius;
	Pos pos;
	Sphere():radius(1){}
	Sphere(const Pos&& pos_, const float radius_)
	{
		radius = radius_;
		pos = pos_;
	}
	Sphere& Create(const Pos& pos_, const float radius_)
	{
		radius = radius_;
		pos = pos_;
		return *this;
	}
};
