#include "GameMain.h"
#include "../Engine/Utilitys/Utility.hpp"
#include <iostream>
void GameMain::UpDate()
{
	controller.UpDate();
}

void GameMain::Draw()
{
	controller.Draw3D();
	controller.Draw2D();
}

bool GameMain::PushEscape()
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

void GameMain::Initialize()
{
	controller.Initialize();
}

void GameMain::Run()
{
	

	while (pEngine.Run() && !PushEscape())
	{
		UpDate();
		Draw();
		Engine::GetFps().Wait();
		DOUT << Engine::GetFps().GetFrameRate() << std::endl;
	}
}

void GameMain::Finalize()
{
	controller.Finalize();
}
