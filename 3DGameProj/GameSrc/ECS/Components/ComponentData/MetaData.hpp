#pragma once
#include "../../Engine.h"
#include "AABB.hpp"
#include "Sphere.hpp"
#include "../../Utilitys/Easing.hpp"

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
		GETAWAY,	//“¦‘–’†
		DEATH		//€–S
	};
	long long id;
	State state;
	int lifeSpan;			//õ–½
	AABB aabb;				//ƒRƒŠƒWƒ‡ƒ“‚ÌŒ`ó
	Pos trackingTarget;		//’ÇÕ‘ÎÛ
	Easing upMove;
	TransForm trans;
};

struct ToppingData
{
	enum class State
	{
		EFFECTIVE,		//—LŒø(’ÇÕ‰Â”\)
		INVALID,		//–³Œø(’ÇÕ–³Œø,º‚í‚ê‚Ä‚¢‚é)
		DEATH			//€–S
	};
	Easing sucked;
	long long id;
	State state;
	Sphere sphere;
	TransForm trans;
};

enum class GameState
{
	PLAY,		//ƒQ[ƒ€’†
	STOP,		//’â~’†
	RESET		//‚·‚×‚Ä‚ÌEntity‚Ì‰Šú‰»ˆ—‚ğŒÄ‚Ô
};