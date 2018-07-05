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

GameMain::GameMain(Engine& engine):
	pEngine(engine)
{
	

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
	while (pEngine.Run())
	{
		UpData();
		Draw();
	}
}

void GameMain::Finalize()
{
	controller.Finalize();
}
