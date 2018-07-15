#pragma once
#include "../../Engine.h"
class EnemyMovements
{
public:
	virtual void UpDate(Vec3&& pos, Vec3&& angle, Vec3&& Velocity) = 0;
};

