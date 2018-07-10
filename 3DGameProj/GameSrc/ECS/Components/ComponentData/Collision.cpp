#include "Collision.h"

bool Collison::BoxCollision(Box& a, Box& b)
{
	Vec3 Min, Min2;
	Vec3 Max, Max2;
	Min = a.GetPos() - a.GetScale();
	Min2 = a.GetPos() - b.GetScale();
	Max = a.GetPos() + a.GetScale();
	Max2 = b.GetPos() + b.GetScale();
	if (Min.x < Max2.x && Max.x > Min2.x
		&& Min.y < Max2.y && Max.y > Min2.y
		&& Min.z < Max2.z && Max.z > Min2.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collison::SphereCollision(Sphere&& s1, Sphere&& s2)
{
	if ((s2.GetPos().x - s1.GetPos().x) * (s2.GetPos().x - s1.GetPos().x) +
		(s2.GetPos().y - s1.GetPos().y) * (s2.GetPos().y - s1.GetPos().y) +
		(s2.GetPos().z - s1.GetPos().z) * (s2.GetPos().z - s1.GetPos().z) <=
		(s1.GetRadius() + s2.GetRadius()) * (s1.GetRadius() + s2.GetRadius()))
	{
		return true;
	}
	else
	{
		return false;
	}
}
