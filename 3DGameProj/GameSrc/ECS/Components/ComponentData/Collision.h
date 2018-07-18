#pragma once
#include "Sphere.hpp"
#include "AABB.hpp"
class Collison
{
private:
	//�_p��AABB�Ƃ̋����̕���
	static float SquarePointAABB(const Vec3&& p, const AABB&& b);
	//�_p��AABB�Ƃ̍Őڋߓ_
	static void ClosestPointAABB(Vec3&& res, const Vec3&& p, const AABB&& b);

public:
	//AABB��AABB
	static bool AABBCollision(AABB&& b, AABB&& b2);
	//���Ƌ�
	static bool SphereCollision(Sphere&& s1, Sphere&& s2);
	//��a��AABB�̐ڐG����
	static bool SphereAABBCollision(const Sphere&& a, const AABB&& b);
	//��a��AABB�̐ڐG���� & �Őڋߓ_
	static bool SphereAABBCollision(Vec3&& res, const Sphere&& a, const AABB&& b);
	//���ƌ���(p + td)�Ƃ̌�������
	static  bool RaySphereCollision(const Vec3&& p, const Vec3&& d, const Sphere&& s);
	//���ƌ���(p + td)�Ƃ̌�������ƌ����_
	static bool RaySphereCollision(Vec3&& res, float& res_t, const Vec3&& p, const Vec3&& d, const Sphere&& s);
	//���Ɛ���(start, end)�Ƃ̌�������
	static bool LineSphereCollision(Vec3&& res, float& res_t, const Sphere&& volume, const Vec3&& pos_start, const Vec3&& pos_end);
	//�_p0��p1��AABB�Ƃ̌�������
	static bool SegmentAABBCollision(const Vec3&& p0, const Vec3&& p1, const AABB&& b);

};