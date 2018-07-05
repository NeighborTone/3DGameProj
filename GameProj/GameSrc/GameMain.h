#pragma once
#include "../Engine/Engine.h"
#include "./GameController/GameController.h"
class GameMain
{
private:
	Engine& pEngine;
	GameController controller;
	void UpData();
	void Draw();
public:
	GameMain(Engine& engine);
	~GameMain();
	void Init();
	void Run();
	void Finalize();
};