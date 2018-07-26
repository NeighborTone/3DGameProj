#pragma once
#include "../../Engine.h"
#include "AABB.hpp"
#include "Sphere.hpp"

struct TransForm
{
	Pos pos;				//���W
	Scale scale;			//�傫��
	Angles angles;			//�p��
	Velocity velocity; 		//������ړ��ʂ��i�[
};

struct ShotData
{
	bool isActive;				//�L����
	int cnt;					//����
	TransForm trans;
};

struct EnemyData
{
	enum class State
	{
		TRACKING,	//�ǐՒ�
		GETAWAY,		//������
		DEATH			//���S
	};
	State state;
	int lifeSpan;				//����
	AABB aabb;				//�R���W�����̌`��
	Pos trackingTarget;		//�ǐՑΏ�
	TransForm trans;
};

struct ToppingData
{
	enum class State
	{
		EFFECTIVE,		//�L��
		INVALID,			//����(�����Ă���)
		DEATH				//���S

	};
	State state;
	Sphere sphere;
	TransForm trans;
};