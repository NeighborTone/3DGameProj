#pragma once
#include "../../Engine.h"
#include "AABB.hpp"
#include "Sphere.hpp"
#include "../../Utilitys/Easing.hpp"

struct [[nodiscard]] TransForm
{
	Pos pos;			//���W
	Scale scale;		//�傫��
	Angles angles;		//�p��
	Velocity velocity; 	//������ړ��ʂ��i�[
	TransForm():
		pos(0,0,0),
		scale(1,1,1),
		angles(0,0,0),
		velocity(0,0,0)
	{}
};

struct [[nodiscard]] ShotData
{
	bool isActive;			//�L����
	int cnt;				//����
	TransForm trans;
};

struct [[nodiscard]] EnemyData
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

struct [[nodiscard]] TomatoData
{
	enum class State
	{
		EFFECTIVE,		//�L��(�ǐՉ\)
		INVALID,		//����(�ǐՖ���,�����Ă���)
		DEATH			//���S
	};
	Easing easeSucked;
	long long id;
	State state;
	Sphere sphere;
	TransForm trans;
};

struct[[nodiscard]] ScoreData
{
	Easing ease;
	Float4 colorDelta;	//�F�̕ω���
	Float4 color;
	TransForm trans;
	long long score;
};

struct RankData
{
	ScoreData scoreData;
	bool isHighScore;
};

struct [[nodiscard]] UIData
{
	Float4 colorDelta;
	Easing ease;
	Float4 color;
	TransForm trans;
};

enum class [[nodiscard]] GameState : short
{
	TITLE,	//�^�C�g��
	PLAY,	//�Q�[����
	PAUSE,	//��~��
	RESET,	//���ׂĂ�Entity�̏������������ĂԁB�X�V��������1�x�������������s�������̂ŗp�ӂ���
	END,	//�Q�[���I��
};
