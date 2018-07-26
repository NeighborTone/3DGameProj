#pragma once
#include "../../Engine.h"
#include "AABB.hpp"
#include "Sphere.hpp"

struct TransForm
{
	Pos pos;				//À•W
	Scale scale;			//‘å‚«‚³
	Angles angles;			//p¨
	Velocity velocity; 		//Œü‚«‚âˆÚ“®—Ê‚ğŠi”[
};

struct ShotData
{
	bool isActive;				//—LŒø‚©
	int cnt;					//õ–½
	TransForm trans;
};

struct EnemyData
{
	enum class State
	{
		TRACKING,	//’ÇÕ’†
		GETAWAY,		//“¦‘–’†
		DEATH			//€–S
	};
	State state;
	int lifeSpan;				//õ–½
	AABB aabb;				//ƒRƒŠƒWƒ‡ƒ“‚ÌŒ`ó
	Pos trackingTarget;		//’ÇÕ‘ÎÛ
	TransForm trans;
};

struct ToppingData
{
	enum class State
	{
		EFFECTIVE,		//—LŒø
		INVALID,			//–³Œø(º‚í‚ê‚Ä‚¢‚é)
		DEATH				//€–S

	};
	State state;
	Sphere sphere;
	TransForm trans;
};