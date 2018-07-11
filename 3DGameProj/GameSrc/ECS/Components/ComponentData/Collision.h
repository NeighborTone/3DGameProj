#pragma once
#include "Sphere.hpp"
#include "Box.hpp"
class Collison
{
public:
	static bool BoxCollision(Box&& a, Box&& b);
	static bool SphereCollision(Sphere&& s1, Sphere&& s2);
};