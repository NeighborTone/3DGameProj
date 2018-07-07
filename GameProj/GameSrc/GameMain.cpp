#include "GameMain.h"
#include "../Engine/Utilitys/Utility.hpp"
void GameMain::UpData()
{
	controller.UpDate();
}

void GameMain::Draw()
{
	controller.Draw3D();
	controller.Draw2D();
}

bool GameMain::Break()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_ESCAPE))
	{
		return true;
	}
	return false;
}

GameMain::GameMain(Engine& engine):
	pEngine(engine)
{
	Mouse::SetMousePos(0, 0);
}

GameMain::~GameMain()
{

}

void GameMain::Init()
{
	controller.Init();
}

void GameMain::Run()
{
	while (pEngine.Run() && !Break())
	{
		UpData();
		Draw();
	}
}

void GameMain::Finalize()
{
	controller.Finalize();
}
