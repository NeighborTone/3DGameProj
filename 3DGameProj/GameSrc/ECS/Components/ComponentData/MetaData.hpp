#pragma once
#include "../../Engine.h"
#include "AABB.hpp"
#include "Sphere.hpp"
#include "../../Utilitys/Easing.hpp"

struct TransForm
{
	Pos pos;				//���W
	Scale scale;			//�傫��
	Angles angles;		//�p��
	Velocity velocity; 	//������ړ��ʂ��i�[
	TransForm():
		pos(0,0,0),
		scale(1,1,1),
		angles(0,0,0),
		velocity(0,0,0)
	{}
};

struct ShotData
{
	bool isActive;			//�L����
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
	long long id;
	State state;
	int lifeSpan;				//����
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
		INVALID,			//����(�ǐՖ���,�����Ă���)
		DEATH				//���S
	};
	Easing sucked;
	long long id;
	State state;
	Sphere sphere;
	TransForm trans;
};

struct ScoreData
{
	Easing ease;
	Float4 color;
	TransForm trans;
	int score;
};

struct UIData
{
	Easing ease;
	Float4 color;
	TransForm trans;
};

enum class GameState : short
{
	TITLE,	//�^�C�g��
	PLAY,	//�Q�[����
	PAUSE,	//��~��
	RESET,	//���ׂĂ�Entity�̏������������ĂԁB�X�V��������1�x�������������s�������̂ŗp�ӂ���
	END,		//�Q�[���I��
};
