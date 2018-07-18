#pragma once
#include "Sphere.hpp"
#include "AABB.hpp"
class Collison
{
private:
	//点pとAABBとの距離の平方
	static float SquarePointAABB(const Vec3&& p, const AABB&& b);
	//点pとAABBとの最接近点
	static void ClosestPointAABB(Vec3&& res, const Vec3&& p, const AABB&& b);

public:
	//AABBとAABB
	static bool AABBCollision(AABB&& b, AABB&& b2);
	//球と球
	static bool SphereCollision(Sphere&& s1, Sphere&& s2);
	//球aとAABBの接触判定
	static bool SphereAABBCollision(const Sphere&& a, const AABB&& b);
	//球aとAABBの接触判定 & 最接近点
	static bool SphereAABBCollision(Vec3&& res, const Sphere&& a, const AABB&& b);
	//球と光線(p + td)との交差判定
	static  bool RaySphereCollision(const Vec3&& p, const Vec3&& d, const Sphere&& s);
	//球と光線(p + td)との交差判定と交差点
	static bool RaySphereCollision(Vec3&& res, float& res_t, const Vec3&& p, const Vec3&& d, const Sphere&& s);
	//球と線分(start, end)との交差判定
	static bool LineSphereCollision(Vec3&& res, float& res_t, const Sphere&& volume, const Vec3&& pos_start, const Vec3&& pos_end);
	//点p0→p1とAABBとの交差判定
	static bool SegmentAABBCollision(const Vec3&& p0, const Vec3&& p1, const AABB&& b);

};