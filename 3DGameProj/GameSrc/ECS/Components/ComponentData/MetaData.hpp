#pragma once
#include "../../Engine.h"
#include "AABB.hpp"
#include "Sphere.hpp"
#include "../../Utilitys/Easing.hpp"

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
		GETAWAY,	//������
		DEATH		//���S
	};
	long long id;
	State state;
	int lifeSpan;			//����
	AABB aabb;				//�R���W�����̌`��
	Pos trackingTarget;		//�ǐՑΏ�
	Easing upMove;
	TransForm trans;
};

struct ToppingData
{
	enum class State
	{
		EFFECTIVE,		//�L��(�ǐՉ\)
		INVALID,		//����(�ǐՖ���,�����Ă���)
		DEATH			//���S
	};
	Easing sucked;
	long long id;
	State state;
	Sphere sphere;
	TransForm trans;
};

enum class GameState
{
	TITLE,		//�^�C�g��
	PLAY,		//�Q�[����
	PAUSE,		//��~��
	RESET		//���ׂĂ�Entity�̏������������Ă�
};