#pragma once
#include "../../Engine.h"
#include "AABB.hpp"
#include "Sphere.hpp"

struct TransForm
{
	Pos pos;				//���W
	Scale scale;			//�傫��
	Angles angles;		//�p��
	Velocity velocity; 	//������ړ��ʂ��i�[
};

struct ShotData
{
	bool isActive;			//�����Ă��邩
	int cnt;					//����
	TransForm trans;
};

struct EnemyData
{
	bool isActive;			//�����Ă��邩
	int lifeSpan;			//����
	AABB aabb;			//�R���W�����p�̌`��
	TransForm trans;
};

struct ToppingData
{
	bool isActive;			//�����Ă��邩
	Sphere sphere;
	TransForm trans;
};