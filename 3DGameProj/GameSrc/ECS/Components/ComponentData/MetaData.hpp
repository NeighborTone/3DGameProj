#pragma once
#include "../../Engine.h"
#include "AABB.hpp"
#include "Sphere.hpp"

struct TransForm
{
	Pos pos;				//座標
	Scale scale;			//大きさ
	Angles angles;		//姿勢
	Velocity velocity; 	//向きや移動量を格納
};

struct ShotData
{
	bool isActive;			//生きているか
	int cnt;					//寿命
	TransForm trans;
};

struct EnemyData
{
	bool isActive;			//生きているか
	int lifeSpan;			//寿命
	AABB aabb;			//コリジョン用の形状
	TransForm trans;
};

struct ToppingData
{
	bool isActive;			//生きているか
	Sphere sphere;
	TransForm trans;
};