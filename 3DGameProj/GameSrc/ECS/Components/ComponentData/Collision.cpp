#include "Collision.h"

bool Collison::AABBCollision(AABB&& a, AABB&& b)
{
	Vec3 Min, Min2;
	Vec3 Max, Max2;
	Min = a.pos - a.radius;
	Min2 = a.pos - b.radius;
	Max = a.pos + a.radius;
	Max2 = b.pos + b.radius;
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
	// a‚Æb‚Ì’†S“_‚Ì‹——£‚Ì•½•û‚ğ‹‚ß‚é
	Vec3 d =s1.GetPos() - s2.GetPos();
	float square = d.Dot(Vec3(d));

	float r = s1.GetRadius() + s2.GetRadius();
	return square <= (r * r);
}

bool Collison::SphereAABBCollision(const Sphere && a, const AABB && b)
{
	float square = SquarePointAABB(Vec3(a.GetPos()), AABB(b));
	return square <= (a.GetRadius() * a.GetRadius());
}

bool Collison::SphereAABBCollision(Vec3 && res, const Sphere && a, const AABB && b)
{
	ClosestPointAABB(Vec3(res), Vec3(a.GetPos()), AABB(b));
	Vec3 v = res - a.GetPos();
	return v.Dot(Vec3(v)) <= (a.GetRadius() * a.GetRadius());
}

bool Collison::RaySphereCollision(const Vec3 && p, const Vec3 && d, const Sphere && s)
{
	Vec3 m = p - s.GetPos();

	float c = m.Dot(Vec3(m)) - s.GetRadius() * s.GetRadius();
	if (c <= 0.0f) return true;

	float b = m.Dot(Vec3(d));
	if (b > 0.0f) return false;

	float disc = b * b - c;
	if (disc < 0.0f) return false;

	return true;
}

bool Collison::RaySphereCollision(Vec3 && res, float & res_t, const Vec3 && p, const Vec3 && d, const Sphere && s)
{
	Vec3 m = p - s.GetPos();

	float b = m.Dot(Vec3(d));
	float c = m.Dot(Vec3(m)) - s.GetRadius() * s.GetRadius();
	if ((c > 0.0f) && (b > 0.0f)) return false;

	float disc = b * b - c;
	if (disc < 0.0f) return false;

	float t = -b - std::sqrt(disc);
	if (t < 0.0f) t = 0.0f;

	res_t = t;

	res = p + d * t;

	return true;
}

bool Collison::LineSphereCollision(Vec3 && res, float & res_t, const Sphere && volume, const Vec3 && pos_start, const Vec3 && pos_end)
{
	return RaySphereCollision(Vec3(res), res_t, Vec3(pos_start), Vec3(pos_end) - Vec3(pos_start).Normalize(),
		Sphere(volume));
}

bool Collison::SegmentAABBCollision(const Vec3 && p0, const Vec3 && p1, const AABB && b)
{
	Vec3 b_max = b.pos + b.radius;
	Vec3 e = b_max - b.pos;
	Vec3 m = (p0 + p1) * 0.5f;
	Vec3 d = p1 - m;
	m = m - b.pos;

	float adx = std::abs(d.x);
	if (std::abs(m.x) > e.x + adx) return false;
	float ady = std::abs(d.y);
	if (std::abs(m.y) > e.y + ady) return false;
	float adz = std::abs(d.z);
	if (std::abs(m.z) > e.z + adz) return false;

	adx += FLT_EPSILON;
	ady += FLT_EPSILON;
	adz += FLT_EPSILON;

	if (std::abs(m.y * d.z - m.z * d.y) > e.y * adz + e.z* ady) return false;
	if (std::abs(m.z * d.x - m.x * d.z) > e.x * adz + e.z* adx) return false;
	if (std::abs(m.x * d.y - m.y * d.x) > e.x * ady + e.y * adx) return false;

	return true;
}

float Collison::SquarePointAABB(const Vec3&& p, const AABB&& b)
{
	{
		float square = 0.0f;
		for (u_int i = 0; i < 3; ++i) {
			float p_min = b.pos(i) - b.radius(i);
			float p_max = b.pos(i) + b.radius(i);
			float v = p(i);
			if (v < p_min) square += (p_min - v) * (p_min - v);
			if (v > p_max) square += (v - p_max) * (v - p_max);
		}
		return square;
	}
}

void Collison::ClosestPointAABB(Vec3 && res, const Vec3 && p, const AABB && b)
{
	for (u_int i = 0; i < 3; ++i) {
		float p_min = b.pos(i) - b.radius(i);
		float p_max = b.pos(i) + b.radius(i);
		float v = p(i);
		if (v < p_min) v = p_min;
		if (v > p_max) v = p_max;
		switch (i)
		{
		case 0:
			res.x = v;
			break;
		case 1:
			res.y = v;
			break;
		case 2:
			res.z = v;
			break;
		}
	}
}