#pragma once
#include "../../Engine.h"
struct EnemyData
{
		bool isActive;
		int life;
		float radius;
		Mesh mesh;
		Vec3 velocity; 	//������ړ��ʂ��i�[
};