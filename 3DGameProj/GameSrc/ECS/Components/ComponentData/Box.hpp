#pragma once
#include "../../../Engine/Engine.h"
#include "../Transform.hpp"

class Box
{
private:
	Pos pos;
	Scale scale;

public:
	Box(const Pos&& pos_, const Scale&& scale_)
	{
		Create(Pos(pos_), Scale(scale_));
	}
	Box Create(const Pos&& pos_, const Scale&& scale_)
	{
		pos.x = pos_.x;
		pos.y = pos_.y;
		pos.z = pos_.z;
		scale.x = scale_.x / 2;
		scale.y = scale_.y / 2;
		scale.z = scale_.z / 2;

		return *this;
	}
	const Pos& GetPos()const
	{
		return pos;
	}
	const Scale& GetScale()const
	{
		return scale;
	}
};

