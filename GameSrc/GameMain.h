#pragma once
#include "../Engine/Engine.h"
#include "./GameController/GameController.h"
class GameMain
{
private:
	Engine& pEngine;
	GameController controller;
	void UpDate();
	void Draw();
	bool PushEscape();
public:
	GameMain(Engine& engine);
	~GameMain();
	void Initialize();
	void Run();
	void Finalize();
};