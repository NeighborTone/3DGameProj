#pragma once
#include "../../../Engine/Engine.h"
#include "../Transform.hpp"

class Box
{
private:
	float
		//ç¿ïW
		x,
		y,
		z,
		//îºåa
		width,
		height,
		depth;
public:
	Box() :x(0), y(0), z(0), width(0), height(0), depth(0) {}
	Box Create(const Pos&& pos, const Scale&& scale)
	{
		x = pos.x;
		y = pos.y;
		z = pos.z;
		width = scale.x / 2;
		height = scale.y / 2;
		depth = scale.z / 2;

		return *this;
	}
	const Pos& GetPos()const
	{
		return Pos(x, y, z);
	}
	const Scale& GetScale()const
	{
		return Scale(width, height, depth);
	}
};

