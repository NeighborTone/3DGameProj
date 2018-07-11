#pragma once
#include "../../../Engine/Engine.h"
#include "../Transform.hpp"
//‹…‘Ì‚Ì’è‹`
class Sphere
{
private:
	float radius_;
	Pos pos_;
public:
	Sphere():radius_(1){}
	Sphere(const Pos&& pos, const float radius)
	{
		radius_ = radius;
		pos_ = pos;
	}
	Sphere& Create(const Pos&& pos,const float radius)
	{
		radius_ = radius;
		pos_ = pos;
		return *this;
	}
	void SetPos(const Pos&& pos)
	{
		pos_ = pos;
	}
	const Pos& GetPos() const
	{
		return pos_;
	}
	const float GetRadius() const
	{
		return radius_;
	}
	
};
